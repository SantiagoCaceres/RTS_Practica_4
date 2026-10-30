# Desarrollo de la práctica 4

## 1. Contexto general

En esta práctica se implementa un sistema didáctico de control longitudinal de una aeronave en Lingua Franca (LF). El objetivo principal es mantener la velocidad aerodinámica cerca de una referencia mediante un lazo de control reactivo, usando módulos periódicos con timers, reactions, ports y conexiones.

La arquitectura del sistema está compuesta por los siguientes módulos:

- `SpeedReference`
- `AirDataSensor`
- `SpeedController`
- `AircraftDynamics`
- `FlightMonitor`
- `DisturbanceProfile`

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

Se implementó un reactor principal que instancia y conecta los cinco módulos funcionales requeridos, junto con el módulo auxiliar `DisturbanceProfile`. Cada módulo usa uno o más timers con el período u offset definido para su función.

### 4.1. `SpeedReference`

Publica la referencia inicial de 100 m/s cada 100 ms. La configuración actual contiene un evento programado a los 20 s para cambiar la referencia a 110 m/s.

### 4.2. `AirDataSensor`

Recibe la velocidad simulada de la planta, aplica la perturbación vigente y publica `v_med` cada 5 ms. Conserva la última velocidad recibida para poder seguir entregando una medición válida entre actualizaciones de la planta.

### 4.3. `SpeedController`

Cada 10 ms calcula el error entre `v_ref` y `v_med`, aplica la ganancia proporcional (actualmente `Kp = 0.28`) y limita el empuje `u_T` al intervalo [0, 1]. También guarda la referencia recibida para usarla en los cálculos periódicos.

### 4.4. `AircraftDynamics`

Cada 10 ms actualiza el estado de velocidad `v` con la ecuación discreta:

$$
v[k+1] = v[k] + T_s \cdot (a_T \cdot u_T[k] - a_D \cdot v[k])
$$

La planta publica la velocidad actualizada por `v_out`, que se envía al sensor con un retardo lógico de 5 ms.

### 4.5. `FlightMonitor`

Cada 100 ms registra la referencia, la velocidad medida, la velocidad real de la planta y el comando de empuje para observar la respuesta del sistema.

### 4.6. `DisturbanceProfile`

Genera una perturbación de velocidad y la envía al sensor. En la configuración actual, aplica `-5.0 m/s` a partir de 1 s y la retira a los 1.05 s. El sensor suma esta perturbación a la última velocidad real recibida para producir `v_med`.

## 5. Retardo lógico `after` y medición de velocidad

La conexión entre la planta y el sensor se define como:

```lf
plant.v_out -> sensor.v_in after 5 ms;
```

El `after 5 ms` es importante por dos motivos relacionados:

1. **Rompe el ciclo causal instantáneo del lazo de realimentación.** La información recorre `AirDataSensor -> SpeedController -> AircraftDynamics -> AirDataSensor`. Sin un retardo en esa última conexión, el modelo pediría que la medición del sensor dependiera del cálculo de la planta y, a la vez, que el cálculo de la planta dependiera de esa medición en el mismo tiempo lógico. El retardo hace explícito que la muestra de la planta se podrá usar en un instante lógico posterior, en vez de requerir una solución instantánea de ese ciclo.
2. **Alinea la llegada de muestras con los períodos de los reactores.** La planta actualiza `v_out` cada 10 ms y el sensor toma muestras cada 5 ms. Al desplazar la muestra de la planta 5 ms, esta llega en una tag posterior y puede ser procesada por el sensor; no se presupone que una entrada esté presente en el mismo instante lógico en que la planta la produce.

Este retardo es de **tiempo lógico**, no una pausa física (`sleep`) de 5 ms dentro del código. LF agenda la entrega para una tag 5 ms posterior. Así, la dependencia temporal queda representada en el modelo y el scheduler puede ordenar las reactions de manera determinista.

El retardo por sí solo no hace que `v_in` esté presente en todos los ticks del sensor: la planta produce datos cada 10 ms y el sensor se activa cada 5 ms. Por eso la reaction del sensor también conserva la última muestra en `current_speed`. Cuando llega `v_in`, actualiza ese estado; en los demás ticks publica la última velocidad recibida, sumada a la perturbación vigente. Esto evita reemplazar la medida por cero cuando no llega una muestra nueva en ese tick.

## 6. Error encontrado y solución

Durante la ejecución se observó que `v_med` permanecía en cero, aunque `v_real` sí aumentaba. El problema no estaba en la ecuación de la planta: `AircraftDynamics` estaba actualizando correctamente la velocidad. El inconveniente estaba en el sensor.

La medición requiere tanto el retardo lógico de la conexión como el almacenamiento de la última muestra: `after 5 ms` modela la causalidad y el instante de entrega, mientras que `current_speed` permite seguir publicando una medida válida entre actualizaciones de la planta. La reaction del sensor se activa por el timer o por una nueva muestra de `v_in`; si llega una muestra, actualiza el estado y publica `current_speed + current_disturbance`.

## 7. Experimentación con `Kp` y perturbaciones

Se probaron distintos valores de `Kp` para observar cómo cambia la respuesta del lazo. Al aumentar `Kp`, el controlador genera una corrección de empuje mayor para un mismo error entre la referencia y la velocidad medida; al reducirla, la corrección es más moderada. La saturación de `u_T` en el intervalo `[0, 1]` limita el empuje disponible, por lo que también se observó la señal de control junto con `v_ref`, `v_med` y `v_real` en `FlightMonitor`. La configuración actual usa `Kp = 0.28`.

También se programaron perturbaciones en distintos instantes de la simulación para observar cómo el sistema responde ante cambios en la medición y cómo el controlador intenta recuperar la referencia. La configuración actual aplica una perturbación de `-5.0 m/s` entre 1 s y 1.05 s; al desplazar los instantes de aplicación en las pruebas, es posible comparar la respuesta según el punto de la evolución en que se introduce la perturbación.

## 8. Estado actual

Con el retardo lógico y la conservación de la última muestra, la planta mantiene su actualización cada 10 ms y el sensor publica una medición basada en la última velocidad disponible cada 5 ms. En la primera activación puede aparecer `v_med = 0`, porque todavía no se ha recibido una muestra de la planta; en las activaciones siguientes se conserva y publica la última muestra disponible. El monitor permite observar la referencia, la velocidad medida, la velocidad real y el comando de empuje durante la simulación.
