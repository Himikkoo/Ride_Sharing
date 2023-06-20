#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class Driver {
public:
    std::string name;
    std::string currentLocation;
    bool available;

    Driver(std::string name, std::string location, bool available)
        : name(std::move(name)), currentLocation(std::move(location)), available(available) {}
};

double calculateDistance(const std::string& sourceLocation, const std::string& destinationLocation) {
    // Perform distance calculation based on coordinates or other methods
    // In this example, we use a simple distance formula assuming each location is assigned a numeric value
    std::map<std::string, double> locationCoordinates = {
        {"Gandhipuram", 1.0},
        {"Ettimadai", 2.0},
        {"Ukkadam", 3.0},
        {"Railways", 4.0},
        {"Bus Stand", 5.0},
        {"Palakkad", 6.0}
    };

    double sourceCoord = locationCoordinates[sourceLocation];
    double destinationCoord = locationCoordinates[destinationLocation];

    return std::abs(destinationCoord - sourceCoord);
}

bool sortByDistance(const Driver& driver1, const Driver& driver2, const std::string& destinationLocation) {
    double distance1 = calculateDistance(driver1.currentLocation, destinationLocation);
    double distance2 = calculateDistance(driver2.currentLocation, destinationLocation);
    return distance1 < distance2;
}

bool confirmRide(const std::string& driverName) {
    // In a real-world application, you would implement a confirmation mechanism (e.g., sending a notification to the driver)
    // For simplicity, we'll assume the ride is confirmed automatically
    return true;
}

double calculatePrice(double distance) {
    // In a real-world application, you would implement a pricing mechanism based on distance and other factors
    // For simplicity, we'll assume a fixed price per unit distance
    constexpr double pricePerUnitDistance = 2.5;
    return distance * pricePerUnitDistance;
}

void findAvailableDriver(std::map<std::string, std::vector<Driver>>& driverLocations,
                         const std::string& sourceLocation, const std::string& destinationLocation) {
    std::vector<Driver> matchedDrivers;

    // Find available drivers in the source location
    if (driverLocations.find(sourceLocation) != driverLocations.end()) {
        for (auto& driver : driverLocations[sourceLocation]) {
            if (driver.available) {
                matchedDrivers.push_back(driver);
            }
        }
    }

    // Sort drivers by distance to the destination location
    std::sort(matchedDrivers.begin(), matchedDrivers.end(), [&](const Driver& driver1, const Driver& driver2) {
        return sortByDistance(driver1, driver2, destinationLocation);
    });

    // Assign the closest available driver to the user
    if (!matchedDrivers.empty()) {
        Driver& assignedDriver = matchedDrivers.front();

        // Confirm the ride and calculate the price
        if (confirmRide(assignedDriver.name)) {
            double distance = calculateDistance(sourceLocation, destinationLocation);
            double price = calculatePrice(distance);

            std::cout << "Ride confirmed!" << std::endl;
            std::cout << "Assigned driver: " << assignedDriver.name << std::endl;
            std::cout << "Distance: " << distance << " units" << std::endl;
            std::cout << "Price: $" << price << std::endl;

            // Update driver's current location and availability
            assignedDriver.currentLocation = destinationLocation;
            assignedDriver.available = false;
        } else {
            std::cout << "Ride canceled. No driver available." << std::endl;
        }
    } else {
        std::cout << "No available drivers found in the source location." << std::endl;
    }
}

int main() {
    // Driver data structure
    std::map<std::string, std::vector<Driver>> driverLocations;

    // Adding drivers to their respective locations
    driverLocations["Gandhipuram"] = {
        Driver("John", "Gandhipuram", true),
        Driver("Jane", "Gandhipuram", false),
        Driver("Alex", "Gandhipuram", true),
        Driver("Emily", "Gandhipuram", true)
    };

    driverLocations["Ettimadai"] = {
        Driver("David", "Ettimadai", true),
        Driver("Sarah", "Ettimadai", true)
    };

    driverLocations["Ukkadam"] = {
        Driver("Michael", "Ukkadam", true),
        Driver("Lisa", "Ukkadam", true),
        Driver("Ryan", "Ukkadam", false)
    };

    driverLocations["Railways"] = {
        Driver("Daniel", "Railways", true),
        Driver("Emma", "Railways", true),
        Driver("Olivia", "Railways", false)
    };

    driverLocations["Bus Stand"] = {
        Driver("William", "Bus Stand", true),
        Driver("Sophia", "Bus Stand", false)
    };

    driverLocations["Palakkad"] = {
        Driver("Jacob", "Palakkad", true),
        Driver("Ava", "Palakkad", true),
        Driver("Liam", "Palakkad", false)
    };

    // User's source and destination locations
    std::string sourceLocation, destinationLocation;
    std::cout << "Enter your source location: ";
    std::cin >> sourceLocation;
    std::cout << "Enter your destination location: ";
    std::cin >> destinationLocation;

    // Find available drivers in the source location and assign the closest driver to the user
    findAvailableDriver(driverLocations, sourceLocation, destinationLocation);

    return 0;
}
