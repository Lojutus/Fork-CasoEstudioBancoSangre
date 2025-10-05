#include <gtest/gtest.h>
#include "../BloodDatabase.h"
//CENTRO DE TESTEO UNITARIO
//Prueba de la funcion de Estadistica de donantes por tipo de sangre y zona
TEST(BloodDatabaseTest, ReportDonorsByBloodTypeAndZone) {
    BloodDatabase db;
    BloodDatabase::DonorsData stats = db.readDataFromFileAndSaveStats();
    // Verificar que los datos se hayan leído correctamente
    EXPECT_FALSE(stats.totalDonorsByZone.empty());
    EXPECT_FALSE(stats.donorsByZoneAndType.empty());

    // Llamar a la función de reporte (esto imprimirá en consola)
    db.report(stats);

    // Aquí podrías agregar más verificaciones específicas según los datos en data.txt
    // Por ejemplo, verificar conteos específicos si conoces los datos de antemano
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
