#include "Components/Reader/Reader.hpp"
#include "Components/Tester/tester.cpp"
#include "Components/Vtk_Builder/vtk_builder.hpp"
#include <iostream>
int main(int argc, char **argv)
{
    if (argc > 1 && std::string(argv[1]) == "--run-tests")
    {
        // Ejecutar las pruebas
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else
    {
        int option;
        Reader csv;
        Octree octree;
        Vtk_Builder vtkBuilder;
        int n;

        std::cout << "Seleccione una opcion:" << std::endl;
        std::cout << "1. Gato" << std::endl;
        std::cout << "2. Dragon" << std::endl;
        std::cout << "3. Five Points" << std::endl;
        std::cout << "4. GTEST" << std::endl;
        std::cin >> option;
        if (option == 1)
        {
            octree = csv.readAndConvert(1);
            vtkBuilder.loadOctree(octree);
        }
        else if (option == 2)
        {
            octree = csv.readAndConvert(2);
            vtkBuilder.loadOctree(octree);
        }
        else if (option == 3)
        {
            octree = csv.readAndConvert(3);
            vtkBuilder.loadOctree(octree);
        }
        else if (option == 4)
        {
            testing::InitGoogleTest();
            return RUN_ALL_TESTS();
        }
        else
        {
            std::cout << "Opción inválida." << std::endl;
            return 1;
        }
        // Menú principal
        int choice;
        do
        {
            std::cout << "\nSeleccione una operación:" << std::endl;
            std::cout << "1. Imprimir Octree" << std::endl;
            std::cout << "2. Buscar punto" << std::endl;
            std::cout << "3. Graph in VTK" << std::endl;
            std::cout << "4. Salir" << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                octree.print();
                break;
            case 2:
                int x, y, z;
                std::cout << "Ingrese las coordenadas (x, y, z) del punto a buscar: ";
                std::cin >> x >> y >> z;
                octree.find(Vec3D(x, y, z)) ? std::cout << "El punto existe en el Octree." << std::endl : std::cout << "El punto no existe en el Octree." << std::endl;
                break;
            case 3:
                vtkBuilder.render();
                vtkBuilder.startInteractor();
                break;
            case 4:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
            }
        } while (choice != 3);
    }
    return 0;
}
