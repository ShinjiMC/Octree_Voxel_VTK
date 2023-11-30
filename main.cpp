#include "converter.hpp"

int main()
{
    int option;
    Converter csv;
    Octree octree;
    int n;

    std::cout << "Seleccione unaD opcion:" << std::endl;
    std::cout << "1. Gato" << std::endl;
    std::cout << "2. Dragon" << std::endl;
    std::cout << "3. TEST" << std::endl;
    std::cin >> option;
    // https://github.com/bertaye/Octree/blob/main/example_main.cpp
    if (option == 1)
        octree = csv.readAndConvert(1);
    else if (option == 2)
        octree = csv.readAndConvert(2);
    else if (option == 3)
        octree = csv.readAndConvert(3);
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
        std::cout << "3. Salir" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            octree.print();
            break;
        case 2:
        {
            int x, y, z;
            std::cout << "Ingrese las coordenadas (x, y, z) del punto a buscar: ";
            std::cin >> x >> y >> z;
            octree.find(Vec3D(x, y, z)) ? std::cout << "El punto existe en el Octree." << std::endl : std::cout << "El punto no existe en el Octree." << std::endl;
            break;
        }
        break;
        case 3:
            std::cout << "Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opción inválida." << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}