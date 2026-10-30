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

## Inicio del desarrollo del módulo `AircraftDynamics`

El módulo `AircraftDynamics` será el punto de partida para la implementación de la dinámica de la aeronave. Su responsabilidad principal es actualizar la velocidad longitudinal simulada a partir del comando de empuje recibido y de la resistencia aerodinámica del sistema.

###  Función principal

El módulo debe:

- recibir el valor del comando de empuje $u_T[k]$,
- usar el estado actual de la velocidad $v[k]$,
- aplicar la ecuación de actualización discreta,
- producir la nueva velocidad $v[k+1]$.

### Ecuación de actualización

La relación discreta propuesta es:

$$
 v[k+1] = v[k] + T_s \cdot (a_T \cdot u_T[k] - a_D \cdot v[k])
$$

Esto permite modelar un sistema de primer orden donde:

- el empuje aumenta la velocidad,
- la resistencia aerodinámica disminuye la velocidad,
- el sistema converge hacia un valor estacionario dependiendo del comando $u_T[k]$.


