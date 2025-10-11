#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "../ValidateInfo.h"
#include "../BloodDatabase.h"
#include "../Console.h"
//CENTRO DE TESTEO UNITARIO
//Prueba de la funcion de Estadistica de donantes por tipo de sangre y zona
TEST(NumberTest, ValidateNumber) {// prueba unitaria para la funcion validateNumber
    ValidateInfo validator;
    EXPECT_TRUE(validator.validateNumberPhone("3136677973")); // Numero valido
    std::this_thread::sleep_for(std::chrono::seconds(1));  //  espera 1 segundo
    EXPECT_FALSE(validator.validateNumberPhone("abcde")); // Numero invalido
}
TEST(DonorTest, SettersAndGetters) {
    Donor d;  // Instanciamos el objeto

    // --- PRUEBAS DE ENTEROS ---
    d.setDonorId(101);
    EXPECT_EQ(d.getDonorId(), 101);

    d.setDistrict(7);
    EXPECT_EQ(d.getDistrict(), 7);

    d.setDonationAmount(500);
    EXPECT_EQ(d.getDonationAmount(), 500);

    // --- PRUEBAS DE STRINGS ---
    d.setName("Carlos Perez");
    EXPECT_EQ(d.getName(), "Carlos Perez");

    d.setAddress("Calle 123, Ciudad Central");
    EXPECT_EQ(d.getAddress(), "Calle 123, Ciudad Central");

    d.setBloodType("O+");
    EXPECT_EQ(d.getBloodType(), "O+");

    d.setNumber("3001234567");
    EXPECT_EQ(d.getNumber(), "3001234567");

    d.setDate("2025-10-05");
    EXPECT_EQ(d.getDate(), "2025-10-05");
}
TEST(BloodDatabaseTest, ReportDonorsByBloodTypeAndZone) {
    BloodDatabase db;
    BloodDatabase::DonorsData stats = db.readDataFromFileAndSaveStats();
    // Verificar que los datos se hayan leído correctamente
    EXPECT_FALSE(stats.totalDonorsByZone.empty());
    EXPECT_FALSE(stats.donorsByZoneAndType.empty());

    // Llamar a la función de reporte (esto imprimirá en consola)
    // db.report(stats);
    
}
TEST(ConsoleValidationTest, NombreValido) {
    Console console;

    // Nombre válido: solo letras y espacios
    std::string result = console.getValidatedStringInput("Carlos Perez", "nombre");
    EXPECT_EQ(result, "Carlos Perez");
}

TEST(ConsoleValidationTest, NombreInvalidoPorNumeros) {
    Console console;

    // Nombre inválido: contiene dígitos
    std::string result = console.getValidatedStringInput("Carlos123", "nombre");

    // Como usa recursión con getInformation, aquí solo verificamos que NO devuelva el mismo valor inválido.
    EXPECT_NE(result, "Carlos123");
}

TEST(ConsoleValidationTest, DireccionValida) {
    Console console;

    std::string result = console.getValidatedStringInput("Av Siempre Viva 742", "address");
    EXPECT_EQ(result, "Av Siempre Viva 742");
}

TEST(ConsoleValidationTest, DireccionInvalida) {
    Console console;

    std::string result = console.getValidatedStringInput("123", "address");
    EXPECT_NE(result, "123");  // Muy corta → debería invalidarse
}

TEST(ConsoleValidationTest, BloodTypeValido) {
    Console console;

    // "1" = tipo de sangre numérico válido
    std::string result = console.getValidatedStringInput("1", "bloodType");
    EXPECT_EQ(result, "1");
}

TEST(ConsoleValidationTest, BloodTypeInvalidoTexto) {
    Console console;

    // No numérico → debe invalidarse
    std::string result = console.getValidatedStringInput("ABC", "bloodType");
    EXPECT_NE(result, "ABC");
}

TEST(ConsoleValidationTest, NumeroTelefonoValido) {
    Console console;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // espera 1 segundo

    // Aquí suponemos que validateNumberPhone() devuelve true para este número
    std::string result = console.getValidatedStringInput("3136677973", "number");
    EXPECT_EQ(result, "3136677973");
}

TEST(ConsoleValidationTest, NumeroTelefonoInvalido) {
    Console console;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Número evidentemente inválido
    std::string result = console.getValidatedStringInput("ABCDE", "number");
    EXPECT_NE(result, "ABCDE");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
