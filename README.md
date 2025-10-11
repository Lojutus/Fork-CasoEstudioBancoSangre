## 🔹 Descripcion basica del proyecto
Este es un caso de Estudio Propuesta en la Clase de progrtamacion orientada a objetos.
Este codigo presenta demasiados errores y nuestro labor es arreglarlo , Este README esta incompleto dado que poco a poco vamos
a estar actualizando el codigo haciendo refactoring de todo el codigo. Ademas del proyecto del banco de sangre de la cruz roja
Se implemento de un proyecto anonimo  un sistema para poder compilar y hacer debug dentro de visual studio gracias a Docker Y 
" devcontainer "

## Funcionamiento:

El programa consta de 3 clases principales con su respectivas definiciones , un sript main Y un archivo txt encargado de guardar los datos  , las clases son las siguientes:
1. **Donor**: La cual es la encargada de representar los donantes, Esta clase posee los sigientes atributos:

    ## Publicos:
    
        getters y setters de: int donorId, district, donationAmount;
        std::string name, address, number, bloodType, date;

        
    ## Privados:

        int donorId, district, donationAmount;
        std::string name, address, number, bloodType, date;
        std::vector<std::string> infoElementsDonorInt
        std::vector<std::string> infoElementsDonorStringTodos los atributos publicos son los que estan encargados de representar diversa informacion que los donantes poseen,
        
    Mientras tanto los atributos privados los cuales son vectores, se encargan de definir el tipo de dato con el que se debe de verificar
    esto se deberia de cambiar en algun futuro.

    Donor tiene los siguientes metodos:

    ## Publicos:

        std::string getItemsDonorInfo
        void donorDetails
        static Donor parseLine
    ## Privados:

        static std::string trim

    **getItemsDonorInfo** Esta estrechamente conectado con los vectores infoElementsDonorInt y infoElementsDonorString Dado que esta funcion busca el elemento recibido en esos dos vectores y devuelve la informacion de donde lo encontro  ( String o int ).

    **parceLine** es una funcion demasiado importante en el sistema de obtener la informacion del archivo txt Dado que este crea un objeto donor y el mismo corta la informacion en cada asignando los valores en este orden : donorId  , name , address, district , bloodType, number, date, donationAmount. El sistema de lectura utiliza stringstream Que funciona como si fuera un cursor, y escanea la linea utilizando getline que lee hasta la coma mas cercada y guarda loq ue leyo en Token el cual se arregla con trim.
    trim organiza los string quitandole espacios al principio y al final 

2. **BloodDatabase**: esta clase se encarga de manejar los datos de los donantes y los donantes como tal , esta clase posee estos atributos:

    ## Publicos:

        struct DonorsData { std::map<int, std::map<std::string, int>> donorsByZoneAndType std::map<int, int> totalDonorsByZone }
    ## Privados:   

        const std::string fileName
        static std::vector<Donor> donors
        std::string bloodTypes

    La estrucutra llamada **DonorsData** es la encargada de almacenar  datos de donantes por zona y tipo de sangre Para poder usarlos luego y usar esa informacion estadistica facilmente.

    **fileName** es el encargado de guardar el nombre del archivo donde tiene la informacion.
    donors es un vector de donantes que se obtuvieron del archivo de texto, elk cual sirve para trabajar facilmente con los donantes sin necesidad de recurrir ela rchvo continuamente.

    **bloodTypes** Contiene un string con los tipos de sangre.

    Esta clase contiene los sigueintes metodos:

    ## Publicos:

        
        
        DonorsData readDataFromFileAndSaveStats
        void report
        void getDonorDetails
        void writeDataToFile
        void searchAndDisplay
        void deleteDonor
        
    ##  Privados:

        static void displayProvinces
        std::string normalizeBloodType
        static std::vector<Donor> getAllDonors
        std::string getZoneName
    **getAllDonors** Devuelve todos los donantes en forma de vector.

    **getZoneName** Apartir del codigo del municipio devuelve el nombre de este mismo.

    **readDataFromFileAndSaveStats** Busca en el vector la informacion relevante y devuelve una estructura DonorsData con la informacion.
    report De acuerdo a la estructura DonorsData que se le suminsitra, este genera un reporte.

    **getDonorDetails** Guarda un donante en el vector

    **writeDataToFile** Escribe los datos del vector en el archivo .txt

    **searchAndDisplay** Busca la informacion en el txt y muestra la informacion de los donantes que concuerdan con el criterio de busqueda 

    **deleteDonor** Elimina un donante en el archivo 

3. **Console** Es la encarga de las utilidades del proyecto, Esta clase no posee atributos, solo posee metodos publicos  .

     ## Publicos:

        static void clearConsole
        static void waitForKeyPres
        static int getValidatedInput
        static std::string getValidatedStringInput
        static std::string getInformation
        static void showInfoMessage
    **clearConsole** Limpia la consola 

    **waitForKeyPres** Espera la confirmacion del usuario

    **getValidatedInput** Verifica el input como un entero y devuelve el input verificado

    **getValidatedStringInput** Verifica el input como un string y devuelve el input verificado

    **getInformation** Devuelve la informacion que se le a pedido al usuario ya verificada 

    **showInfoMessage** Muestra informacion en la consola 
4. **ValidateInfo** Esta clase es la encargada de las verificaciones con API tiene datos sencibles que se deberian de configurar manualmente, tiene estos metodos:
    ## Publicos

        static bool validateNumberPhone

    **validateNumberPhone** Utiliza la API de abstract Para verificar los numeros, Con curls

## Archivo principal
El archivo principal esta constituido por  las iomportanciones necesecsarias y las inicializaciones necesarias , despues entra a un while que sirve como menu , para pedir la opcion que el usuario desea realizar. Despues entra a un switch que sirve como enrutador hacia las funciones de BloodDatabase
        

    



## 🔹 COMO HACER Debugging en VS Code
El archivo `.vscode/launch.json` ya incluye la configuración de depuración:
- Debug (gdbserver :2345) → Permite depuración remota con `gdbserver`.
1. En una terminal del contenedor, compila y lanza `gdbserver`:
```bash
make gdbserver
```
Esto mostrará algo como:
```bash
Listening on port 2345
Waiting for gdb connection...
```
2. En VS Code pulsa **F5**. Se conectará al puerto *2345* y podrás depurar de forma remota.

## 🔹 Google Testing
Se debe modificar el archivo `tests/test_main.cpp` con los test que requeridos.

Dentro del Dev Container:

```bash
make google-test       # Ejecuta los test con la librería gtest de google
```

El binario generado es `test_runner`.

# NOTAS
Es Posible que se pierda acceso a modificar diversos archivos dentro del contanier, si es asi se debe de ejecutar
estando en la carpeta raíz del proyecto
```bash
sudo chown -R $(whoami):$(whoami) .
sudo chmod -R u+rw .
```
