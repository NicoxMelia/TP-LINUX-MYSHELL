# Myshell
# Módulo JobId
Este módulo proporciona una interfaz para manejar un identificador de trabajo (JobId). El JobId es un tipo de dato pid_t que se utiliza para identificar procesos en un sistema operativo.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “jobid.h” en tu código fuente.

## Variables
El módulo define una variable global jobId de tipo pid_t. Esta variable se utiliza para almacenar el identificador del trabajo actual.

## Funciones
El módulo proporciona las siguientes funciones para manipular el JobId:

- **void setJobId(pid_t id):** Esta función establece el valor del JobId. Acepta un argumento de tipo pid_t que es el nuevo valor del JobId.

- **pid_t getJobId():** Esta función devuelve el valor actual del JobId. No acepta ningún argumento.


# Módulo PipeRunner
Este módulo proporciona una interfaz para ejecutar una serie de comandos en un pipeline. Los comandos se ejecutan en procesos separados y la salida de un comando se pasa como entrada al siguiente comando en el pipeline.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “piperunner.h” en tu código fuente.

## Constantes
El módulo define una constante MAX_COMMANDS que especifica el número máximo de comandos que se pueden ejecutar en un pipeline.

## Variables
El módulo define una variable global numCommands de tipo int. Esta variable se utiliza para almacenar el número de comandos en el pipeline actual.

## Funciones
El módulo proporciona las siguientes funciones para manipular pipelines:

- **void preparePipe(char code[]):** Esta función prepara un pipeline para su ejecución. Acepta un argumento de tipo char[] que es una cadena de caracteres que contiene los comandos a ejecutar en el pipeline. Los comandos deben estar separados por el carácter ‘|’. Esta función divide la cadena de comandos en comandos individuales y los almacena en un array. Luego, llama a la función runPipe para ejecutar los comandos.

- **void runPipe(char *commands[], int cant):** Esta función ejecuta los comandos en un pipeline. Acepta dos argumentos: un array de punteros a cadenas de caracteres que contiene los comandos a ejecutar y un entero que especifica el número de comandos en el array. Esta función crea un proceso separado para cada comando y configura las tuberías (pipes) para que la salida de un comando se pase como entrada al siguiente comando en el pipeline.


# Módulo Prompt
Este módulo proporciona una interfaz para imprimir un prompt en la consola. El prompt incluye el nombre de usuario, el nombre del host y el directorio de trabajo actual.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “prompt.h” en tu código fuente.

## Funciones
El módulo proporciona la siguiente función:

- **void printPrompt():** Esta función imprime un prompt en la consola. El prompt tiene el formato usuario@host:directorio$ . La función obtiene el nombre de usuario y el nombre del host utilizando las funciones del sistema gethostname y getlogin_r, respectivamente. El directorio de trabajo actual se obtiene utilizando la función del sistema getenv con el argumento "PWD".


# Módulo RunFile
Este módulo proporciona una interfaz para ejecutar un archivo de código. El archivo se lee línea por línea y cada línea se pasa a una función para su ejecución.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “runfile.h” en tu código fuente.

## Funciones
El módulo proporciona la siguiente función:

- **void runFile(char fileName[]):** Esta función ejecuta un archivo de código. Acepta un argumento de tipo char[] que es el nombre del archivo a ejecutar. La función abre el archivo para lectura y lee el archivo línea por línea. Cada línea leída se pasa a la función start para su ejecución. Después de ejecutar todas las líneas del archivo, la función termina el proceso.


# Módulo Shell
Este módulo proporciona una interfaz para ejecutar comandos en un shell. Los comandos se ejecutan en procesos separados y la salida de un comando se pasa como entrada al siguiente comando en el pipeline.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “runner.h” en tu código fuente.

## Funciones
El módulo proporciona las siguientes funciones para manipular pipelines:

- **bool isPipe(char code[]):** Esta función verifica si el comando ingresado por el usuario contiene un pipe (|).

- **bool isRedirection(char code[]):** Esta función verifica si el comando ingresado por el usuario contiene una redirección (> o <).

- **int isInternal(char code[]):** Esta función verifica si el comando ingresado por el usuario es un comando interno (cd, clr, echo, quit).

- **void start(char code[]):** Esta función inicia el shell. Si el comando ingresado por el usuario es “clr”, se limpia la pantalla. De lo contrario, se llama a la función testMode(code).

- **void getCode(char code[], char aux[]):** Esta función obtiene el código del comando ingresado por el usuario.

- **void testMode(char code[]):** Esta función prueba el modo del comando ingresado por el usuario. Si el comando contiene un pipe, se prepara el pipe. Si el comando es interno, se ejecuta en primer o segundo plano dependiendo de si contiene un ‘&’. Si el comando no es interno, se ejecuta como un comando externo en primer o segundo plano dependiendo de si contiene un ‘&’.

- **void runForeground(char code[]):** Esta función ejecuta un comando interno en primer plano.

- **void runBackground(char code[]):** Esta función ejecuta un comando interno en segundo plano.

- **void runExternal(char code[], bool bg):** Esta función ejecuta un comando externo. Si bg es verdadero, el comando se ejecuta en segundo plano. De lo contrario, se ejecuta en primer plano.

- **void runInternal(char code[]):** Esta función ejecuta un comando interno. Los comandos internos que se pueden ejecutar son “cd”, “clr”, “echo” y “quit”.


# Módulo SigManager
Este módulo proporciona una interfaz para manejar señales en un shell. Las señales son eventos generados por el sistema operativo o por otros programas que pueden ser capturados y manejados por tu programa.

## Inclusión del Módulo
Para utilizar este módulo, necesitas incluir el archivo de cabecera “sigmanager.h” en tu código fuente.

## Funciones
El módulo proporciona las siguientes funciones para manejar señales:

- **void sigchldHandler(int sg):** Esta función maneja la señal SIGCHLD, que es enviada a un proceso cuando uno de sus procesos hijos termina. La función llama a waitpid para esperar a que el proceso hijo termine.

- **void sigtstpHandler(int sg):** Esta función maneja la señal SIGTSTP, que es enviada a un proceso cuando se presiona Ctrl+Z en la terminal. La función llama a kill para enviar la señal SIGTSTP al proceso hijo.

- **void sigintHandler(int sg):** Esta función maneja la señal SIGINT, que es enviada a un proceso cuando se presiona Ctrl+C en la terminal. La función llama a kill para enviar la señal SIGINT al proceso hijo.

- **void sigquitHandler(int sg):** Esta función maneja la señal SIGQUIT, que es enviada a un proceso cuando se presiona Ctrl+\ en la terminal. La función llama a kill para enviar la señal SIGQUIT al proceso hijo.

- **void ignoreSignal(int sg):** Esta función es un manejador de señales vacío que no hace nada. Se puede utilizar para ignorar señales.