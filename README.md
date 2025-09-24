## 🔹 Descripcion basica del proyecto
Este es un caso de Estudio Propuesta en la Clase de progrtamacion orientada a objetos.
Este codigo presenta demasiados errores y nuestro labor es arreglarlo , Este README esta incompleto dado que poco a poco vamos
a estar actualizando el codigo haciendo refactoring de todo el codigo. Ademas del proyecto del banco de sangre de la cruz roja
Se implemento de un proyecto anonimo  un sistema para poder compilar y hacer debug dentro de visual studio gracias a Docker Y 
devcontainer Que se explica a continuacion:

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
Es Posible que se peirda acceso a modificar diversos archivos dentro del contanier, si es asi se debe de ejecutar
estando en la carpeta raíz del proyecto
```bash
sudo chown -R $(whoami):$(whoami) .
sudo chmod -R u+rw .
```
