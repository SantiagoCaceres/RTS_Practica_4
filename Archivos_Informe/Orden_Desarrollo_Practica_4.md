# Desarrollo de la práctica 4

## 1. Contexto general

En esta práctica se implementa un sistema didáctico de control longitudinal de una aeronave en Lingua Franca (LF). El objetivo principal es mantener la velocidad aerodinámica cerca de una referencia mediante un lazo de control reactivo, usando módulos periódicos con timers, reactions, ports y conexiones.

La arquitectura del sistema está compuesta por los siguientes módulos:

- `SpeedReference`
- `AirDataSensor`
- `SpeedController`
- `AircraftDynamics`
- `FlightMonitor`

---

## 2. Preguntas orientadoras y respuestas

### 2.1. ¿Qué diferencia existe entre reactor, reaction, timer, puerto y conexión en LF?

En Lingua Franca, estos cinco elementos constituyen la arquitectura básica del sistema reactivo.

- **Reactor:** Es el bloque principal del sistema, equivalente a un módulo o a un objeto con estado propio. En la práctica, módulos como `SpeedController`, `AirDataSensor` y `AircraftDynamics` son reactors independientes.
- **Reaction:** Es el fragmento de código ejecutable dentro de un reactor. Una reaction queda dormida hasta que es disparada por un evento específico.
- **Timer:** Es un disparador interno que genera eventos en instantes de tiempo lógico, ya sea una sola vez o periódicamente. Se usa para activar módulos con la frecuencia requerida.
- **Puerto (Port):** Es la interfaz de entrada o salida de un reactor. Permite intercambiar información sin que cada reactor conozca los detalles internos del otro.
- **Conexión (Connection):** Es el enlace entre el puerto de salida de un reactor y el puerto de entrada de otro. Define la dependencia causal y asegura el orden válido de ejecución.

### 2.2. ¿Qué representa una tag (tiempo lógico y microstep)? ¿Pueden ejecutarse dos reactions con la misma etiqueta temporal?

Una **tag** en LF representa el instante lógico exacto en que ocurre un evento y está compuesta por:

- **Tiempo lógico**: el instante temporal del sistema.
- **Microstep**: un número entero que ordena eventos simultáneos dentro del mismo instante lógico.

Sí, pueden ejecutarse dos o más reactions con la misma etiqueta temporal. Eso significa que ocurren “al mismo tiempo” desde la perspectiva lógica del sistema. El orden físico real depende de las dependencias causales y del scheduler de LF.

### 2.3. ¿Por qué el período lógico no equivale necesariamente al intervalo físico medido entre el inicio de dos ejecuciones de un módulo o tarea periódica?

El período lógico es el intervalo ideal definido por la semántica del modelo, mientras que el intervalo físico es el tiempo real observado en la CPU. La diferencia entre ambos se conoce como **jitter** y se debe a:

- latencias del sistema operativo,
- sobrecarga del scheduler,
- interrupciones,
- retardo de ejecución de reactions,
- dependencias causales entre módulos.

Por esta razón, el tiempo lógico y el tiempo físico no siempre coinciden exactamente, aunque el sistema se haya diseñado para ejecutar periódicamente.

### 2.4. ¿Qué ventajas ofrece expresar la comunicación mediante puertos y conexiones frente a implementar manualmente hilos y variables compartidas con POSIX?

La comunicación con puertos y conexiones en LF ofrece varias ventajas:

- evita variables compartidas,
- reduce errores por sincronización y condiciones de carrera,
- clarifica el orden causal de ejecución,
- facilita la composición modular del sistema,
- permite modelar explícitamente el flujo de datos y el comportamiento reactivo.

En cambio, el uso de hilos y variables compartidas con POSIX suele requerir más control manual y es más propenso a errores de concurrencia y coordinación.

---

## Parámetros propuestos para la planta

Se definen los siguientes parámetros para la dinámica discreta del sistema:

- $T_s = 0.01\,\text{s}$ (10 ms, dado por el período requerido de la planta)
- $a_T = 15.0\,\text{(m/s}^2\text{)}$
- $a_D = 0.05\,\text{(1/s)}$

### Justificación del informe

Seleccionamos un valor de resistencia $a_D = 0.05$ de forma didáctica para garantizar que el sistema disipe energía y tienda a un estado estacionario estable. Elegimos $a_T = 15.0$ para que, ante un comando de empuje máximo saturado ($u_T = 1$), el sistema pueda alcanzar y mantener referencias de velocidad aerodinámica razonables (alrededor de 100 m/s a 300 m/s) en estado estacionario, simulando el comportamiento acotado del control longitudinal de la aeronave.

Además, el valor de $T_s = 0.01\,\text{s}$ se selecciona acorde con el período requerido por la planta y con la estructura multi-rate propuesta en la práctica.

La ecuación de la dinámica longitudinal queda entonces establecida como:

$$
 v[k+1] = v[k] + T_s \cdot (a_T \cdot u_T[k] - a_D \cdot v[k])
$$

donde:

- $v[k]$ es la velocidad aerodinámica simulada,
- $u_T[k]$ es el comando de empuje normalizado,
- $a_T$ representa la eficacia del empuje,
- $a_D$ representa la resistencia aerodinámica,
- $T_s$ es el período de actualización de la planta.

---

## 4. Desarrollo de los módulos

Se implementó un reactor principal que instancia y conecta los cinco módulos requeridos. Cada módulo usa un timer con el período definido para su función.

### 4.1. `SpeedReference`

Publica la referencia inicial de 100 m/s cada 100 ms. También contiene un evento programado a los 2 s para cambiar la referencia a 110 m/s.

### 4.2. `AirDataSensor`

Recibe la velocidad simulada de la planta, aplica la perturbación vigente y publica `v_med` cada 5 ms. Conserva la última velocidad recibida para poder seguir entregando una medición válida entre actualizaciones de la planta.

### 4.3. `SpeedController`

Cada 10 ms calcula el error entre `v_ref` y `v_med`, aplica la ganancia proporcional `Kp = 0.05` y limita el empuje `u_T` al intervalo [0, 1]. También guarda la referencia recibida para usarla en los cálculos periódicos.

### 4.4. `AircraftDynamics`

Cada 10 ms actualiza el estado de velocidad `v` con la ecuación discreta:

$$
v[k+1] = v[k] + T_s \cdot (a_T \cdot u_T[k] - a_D \cdot v[k])
$$

La planta publica la velocidad actualizada por `v_out`, que se envía al sensor con un retardo lógico de 5 ms.

### 4.5. `FlightMonitor`

Cada 100 ms registra la referencia, la velocidad medida, la velocidad real de la planta y el comando de empuje para observar la respuesta del sistema.

## 5. Error encontrado y solución

Durante la ejecución se observó que `v_med` permanecía en cero, aunque `v_real` sí aumentaba. El problema no estaba en la ecuación de la planta: `AircraftDynamics` estaba actualizando correctamente la velocidad. El inconveniente estaba en el sensor.

La reacción original del sensor se activaba con su timer de 5 ms y leía `v_in` únicamente si esa entrada estaba presente en la misma tag. Sin embargo, la planta publica cada 10 ms y su salida llega al sensor con un retardo de 5 ms. Por lo tanto, `v_in` no está presente en todos los ticks del timer. Cuando no coincidían, el código asignaba cero a la velocidad medida y publicaba ese cero.

La corrección consiste en conservar en el estado `current_speed` la última velocidad recibida. La reacción del sensor se activa tanto por el timer como por una nueva muestra de `v_in`: si llega una muestra, actualiza el estado; en cada activación publica `current_speed + current_disturbance`. Así, cuando no hay una muestra nueva en un tick, se reutiliza la última válida en lugar de reemplazarla por cero.

## 6. Estado actual

Con esta corrección, la planta mantiene su dinámica de actualización cada 10 ms y el sensor publica una medición basada en la última velocidad disponible cada 5 ms. En la primera activación puede aparecer `v_med = 0`, porque todavía no se ha recibido una muestra de la planta; en las activaciones siguientes ya se conserva y publica la última muestra disponible. La compilación y una ejecución corta confirmaron que `v_med` pasa a valores positivos mientras `v_real` aumenta.
