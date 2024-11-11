# Tarea 2 - Splay Trees y ABB's

Esta tarea implementa un Splay Trees y un ABB's en C++.

## Requisitos

- C++17 o superior (Para no tener problema con las librerias)

## Estructura del proyecto

La totalidad del codigo se encuentra dentro de `T2.cpp`

## Configuración

La función `main()` que ejecuta los experimentos se encuentra dentro de `T2.cpp`.

Dentro de `T2.cpp` podemos configurar principalmente las variaciones del parametro i, el cual corresponde
al porcentaje de puntos que se tomaran respecto a $10^6$.

Por defecto `main()` viene configurado de la siguiente forma:


- Cantidad de puntos $10^6 \cdot i$. 
  
Con $i \in \{0.1, ..., 1.0\}$

```c++
for (float i = 0.1; i <= 1; i += 0.1)
```


> [!NOTE]
> Todos estos valores por defecto, son los mismos pedidos en el enunciado de la tarea.

## Ejecucion

El `main` esta configurado para que a partir de la configuración inicial, se ejecuten **todos** los experimentos.

Para poder compilar el proyecto se requiere:

- Usar la extension de C/C++ de VSCode

## Extensión C/C++

### Requerimientos

- VSCode
- Extensión de C++ para Visual Studio Code

Para esta forma de ejecutar, recomendamos seguir la documentación oficial de la extension y de VSCode.

- [Windows](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites)
- [Linux](https://code.visualstudio.com/docs/cpp/config-linux)

> [!NOTE]
> Estos tutoriales, lo que hacen es usar `g++` como compilador de C, y mostrar como ser configurado para VSCode usando la extension. En particular para Windows, se debe instalar `MinGW-w64` para poder tener el compilador de C en Windows (mas información en el tutorial).

La extension de C++, al configurarse como se muestra en el tutorial (seccion _"Run helloworld.cpp"_, punto 2 y 3), se generan varios archivos `.json` para compilar un proyecto. En particular, genera uno llamado `tasks.json`, el cual tiene los parametros que luego son entregado a `g++`.

Finalmente se debe ejecutar `main.cpp` usando la extension, lo cual compila y genera un ejecutable `main.exe` que debe ser ejecutado como un programa normal.

```bash
$ main.exe
```
> [!NOTE]
> Lo que hace la extension es ejecutar `g++` con la configuración de `tasks.json` de una forma mas automática y mas simple, pero de todas formas se puede ejecutar manualmente. [Aquí están los links de los comandos de g++ (o preguntarle a Mateu 🙂)](https://courses.cs.washington.edu/courses/cse326/00wi/unix/g++.html).


> [!IMPORTANT]
> Se recalca la importancia de seguir los tutoriales de la extensión de C++ para VSCode debido a que esta fue la forma de ejecución del grupo. Cualquier otro método queda fuera del alcance de lo probado.


## Experimentos

Al ejecutar los experimentos, se genera un archivo `data.tsv` en el directorio raiz del proyecto. Este contiene diversas metricas calculadas durante el experimento. Adicionalmente, dentro de `/experiments_data/` se pueden encontrar los datos obtenidos por el equipo.