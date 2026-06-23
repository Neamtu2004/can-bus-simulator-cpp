#include <iostream>
#include "CanBus.h"
#include "EngineECU.h"
#include "ABSNode.h"
#include "Dashboard.h"

int main()
{
    // Creaza magistrala
    CanBus bus;

    // Creaza nodurile
    EngineECU engine(3500, 90.5f);  // 3500 RPM, 90.5°C
    ABSNode abs(120.0f);             // 120 km/h
    Dashboard dashboard;

    // Conecteaza nodurile la bus
    bus.addNode(&engine);
    bus.addNode(&abs);
    bus.addNode(&dashboard);

    std::cout << "=== EngineECU trimite date ===" << std::endl;
    engine.sendData(bus);

    std::cout << "\n=== ABSNode trimite date ===" << std::endl;
    abs.sendData(bus);

    return 0;
}