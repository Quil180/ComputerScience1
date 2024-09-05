/* COP 3502C Assignment 1
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 21

// structures that I must include
typedef struct RegisteredVehicle { // for one registered vehicle
  char *license_plate; // string for license plate
  char *owner_name; // string for owner of vehicle
} RegisteredVehicle;

typedef struct Garage { // for one garage
  char *garage_name; // string for name of garage
  int total_capacity; // total capacity of garage
  int current_count; // vehicles parked in a particular time
  RegisteredVehicle **parked_vehicles; // list of parked vehicles in a particle time
} Garage;

typedef struct Campus {
  Garage **garages; // list of garages on campus
  int total_garages; // number of garages on campus
  RegisteredVehicle **registered_vehicles; // list of all registered vehicles
  int total_registered_vehicles; // total number of registered vehicles
} Campus;

// Functions I must implement
Garage *createGarage(const char *name, int capacity) { // creates a new garage and initializes it
  Garage *garage = calloc(1, sizeof(Garage)); // creating the garage via DMA
  garage->garage_name = calloc(strlen(name)+1, sizeof(char)); // creating the name of the string via DMA
  strcpy(garage->garage_name, name); // putting the name of the garage into the structure
  garage->total_capacity = capacity; // giving it the total capacity
  garage->parked_vehicles = calloc(capacity, sizeof(RegisteredVehicle)); // creating the array of parked vehicles with size of the max capacity
  garage->current_count = 0; // initializing the current capacity of the garage to be 0

  return garage;
};

RegisteredVehicle *createRegisteredVehicle(const char *license, const char *owner) { // create a new vehicle registry
  RegisteredVehicle *vehicle = calloc(1, sizeof(RegisteredVehicle));
  
  // allocating the memory for both the name and license plate
  vehicle->owner_name = calloc(strlen(owner)+1, sizeof(char));
  vehicle->license_plate = calloc(strlen(license)+1, sizeof(char));
  // copying the values of the license and owner to the vehicle registrigation
  strcpy(vehicle->owner_name, owner);
  strcpy(vehicle->license_plate, license);

  // returning the newly made vehicle's pointer
  return vehicle;
};

void registerVehicle(Campus *campus, const char *license, const char *owner) { // register a new vehicle on campus
  campus->total_registered_vehicles += 1;
  campus->registered_vehicles = (RegisteredVehicle **)realloc(campus->registered_vehicles, campus->total_registered_vehicles * sizeof(RegisteredVehicle));
  campus->registered_vehicles[campus->total_registered_vehicles-1] = createRegisteredVehicle(license, owner);
}

void parkVehicle(Garage *garage, RegisteredVehicle *vehicle) { // park a vehicle at a garage. If full, print FULL, other park and print PARKED
  if (garage->current_count == garage->total_capacity) {
    printf("FULL\n");
  } else {
    garage->parked_vehicles[(garage->current_count)] = vehicle;
    garage->current_count += 1;
    printf("PARKED\n");
  }
}

int removeVehicleFromGarage(Garage *garage, const char *license) { // remove vehicle from a garage. Return 1 if succesful otherwise return 0
  int i = 0;
  RegisteredVehicle *temp;
  while (garage->parked_vehicles[i]->license_plate == license) {
    i++;
  }
  if (i != garage->current_count) {
    return 0;
  }
  for (int j = i+1; j < garage->current_count; j++) {
    if (j-1 == 0) {
      garage->parked_vehicles[j-1] = garage->parked_vehicles[j];
    } else if (j == garage->current_count) {
      garage->parked_vehicles[j] = NULL;
    }
  }
  garage->current_count -= 1;
  return 1;
}

RegisteredVehicle *searchVehicleByLicense(const Campus *campus, const char *license) { // search for vehicle by license. If found return vehicle, else return NULL
  int i = 0;
  while (strcmp(license, campus->registered_vehicles[i]->license_plate) != 0) {
    i++;
  }
  return campus->registered_vehicles[i];
};

int countTotalVehicles(const Campus *campus) { // returns number of vehicles parked on campus
  int total = 0;
  for (int i = 0; i < campus->total_garages; i++) {
    total += campus->garages[i]->current_count;
  }
  return total;
}

int resizeGarage(Garage *garage, int new_capacity) { // resizes garage to new capacity. If capacity smaller than vehicles parked, print FAIL. TOO SMALL TO ACCOMODATE EXISTING VEHICLES. Return 1 or 0 depending on if successful or not.
  if (garage->current_count > new_capacity) {
    printf("FAIL. TOO SMALL TO ACCOMMODATE EXISTING VEHICLES.\n");
    return 0;
  } else {
    garage->parked_vehicles = (RegisteredVehicle **)realloc(garage->parked_vehicles, new_capacity * sizeof(RegisteredVehicle));
    garage->total_capacity = new_capacity;
    printf("SUCCESS\n");
    return 1;
  }
}

int relocateVehicle(Campus *campus, const char *license, const char *target_garage_name) { // relocate vehicle to another garage. If garage not found, print [G] NOT FOUND. If garage full, print [G] IS FULL. Return 1 or 0 if successful or not.
  int foundvehicleingarage;
  // finding the vehicle we want to transfer
  RegisteredVehicle *temp = searchVehicleByLicense(campus, license);
  for (int i = 0; i < campus->total_garages; i++) {
    for (int j = 0; j < campus->garages[i]->current_count; j++) {
      if (strcmp(license, campus->garages[i]->parked_vehicles[j]->license_plate) == 0) {
        foundvehicleingarage = removeVehicleFromGarage(campus->garages[i], temp->license_plate);
      }
    }
  }
  if (foundvehicleingarage == 0) {
    printf("%s NOT IN CAMPUS\n", license);
    return 0;
  } else {
    // searching for every garage for the target garage
    for (int i = 0; i < campus->total_garages; i++) {
      if (strcmp(campus->garages[i]->garage_name, target_garage_name) == 0) {
        if (campus->garages[i]->current_count == campus->garages[i]->total_capacity) {
          printf("%s IS FULL\n", target_garage_name);
          return 0;
        }
        // parking the vehicle proper
        parkVehicle(campus->garages[i], temp);
        printf("RELOCATION SUCCESSFUL\n");
        return 1;
      }
    }
    printf("%s NOT FOUND\n", target_garage_name);
    return 0;
  }
}

void displayVehiclesByOwner(const Campus *campus, const char *owner_name) {
  int i, gi, gj;
  int vehicle_found, numvehicles;

  for (i = 0; i < campus->total_registered_vehicles; i++) {
    if (strcmp(owner_name, campus->registered_vehicles[i]->owner_name) == 0) {
      vehicle_found = 0;

      // Check if the vehicle is in any garage
      for (gi = 0; gi < campus->total_garages; gi++) {
        for (gj = 0; gj < campus->garages[gi]->current_count; gj++) {
          if (strcmp(campus->registered_vehicles[i]->license_plate, campus->garages[gi]->parked_vehicles[gj]->license_plate) == 0) {
            vehicle_found = 1;
            numvehicles += 1;
            // Print the vehicle and garage information
            printf("%s %s\n", campus->registered_vehicles[i]->license_plate, campus->garages[gi]->garage_name);
            // No need to search further for this vehicle
          }
        }
      }

      if (!vehicle_found) {
        numvehicles += 1;
        printf("%s NOT ON CAMPUS\n", campus->registered_vehicles[i]->license_plate);
      }
    }
  }
  if (numvehicles == 0) {
    printf("NO REGISTERED CAR BY THIS OWNER\n");
  }
}


int removeGarage(Campus *campus, const char *garage_name) { // remove a garage, and free its memory. Do not remove the vehicles from the system. Return 1 or 0 depnding on success.
  int i = 0;
  if (strcmp(campus->garages[i]->garage_name, garage_name) != 0) {
    i++;
    if (i >= campus->total_garages) {
      return 0;
    }
  } else {
    free(campus->garages[i]->garage_name);
    free(campus->garages[i]->parked_vehicles);
    free(campus->garages[i]);
  }
  return 1;
}

void generateGarageUtilizationReport(const Campus *campus) { // generate a report on all garage. print the following:
  // Garage: [G], Capacity: [GC], Occupied: [GO], Utilization: [GU]%
  // After this print the name of the garage which is utilized the least.
  double utilizedi = 100.00;
  int j = 0;
  for (int i = 0; i < campus->total_garages; i++) {
    printf("Garage: %s, Capacity: %d, Occupied: %d, Utilization: %0.2f%%\n", campus->garages[i]->garage_name, campus->garages[i]->total_capacity, campus->garages[i]->current_count, 100.00*(campus->garages[i]->current_count)/(campus->garages[i]->total_capacity));
    if (utilizedi > 100.00*(campus->garages[i]->current_count)/(campus->garages[i]->total_capacity)) {
      j = i;
      utilizedi = 100.00*(campus->garages[i]->current_count)/(campus->garages[i]->total_capacity);
    }
  }
  printf("Least Utilized: %s\n", campus->garages[j]->garage_name);
}

// the following functions that I made.

Campus *createCampus(int *c) { // the function that takes in all of the initial data
  int i=0, j=0, size=0;
  char name[MAXSTRING];
  char license[MAXSTRING];
  Campus *campus = calloc(1, sizeof(Campus));
  // getting the amount of garages, vehicle amount at start (parked and not parked), and amount of commands total
  scanf("%d", &(campus->total_garages));
  scanf("%d", &(campus->total_registered_vehicles));
  scanf("%d", c);
  campus->garages = calloc(campus->total_garages, sizeof(Garage)); // allocating the memory for number of garages, g.
  for (i = 0; i < campus->total_garages; i++) {
    scanf("%s %d",name, &size);
    campus->garages[i] = createGarage(name, size);
  }

  campus->registered_vehicles = calloc(campus->total_registered_vehicles, sizeof(RegisteredVehicle)); // making the array of vehicles
  // creating the registry of vehicles
  for (i = 0; i < campus->total_registered_vehicles; i++) {
    scanf("%s %s", license, name);
    campus->registered_vehicles[i] = createRegisteredVehicle(license, name);
  }

  return campus;
};

void removeVehicleGarage(Campus *campus, char *arg1, int *arg1i) {
  scanf("%s", arg1);
  if (strcmp(arg1, campus->registered_vehicles[*arg1i]->license_plate) != 0) {
    arg1i++;
  }
  for (int i = 0; i < campus->total_garages; i++) {
    for (int k = 0; k < campus->garages[i]->current_count; k++) {
      if (campus->registered_vehicles[*arg1i]->license_plate == campus->garages[i]->parked_vehicles[k]->license_plate) {
        removeVehicleFromGarage(campus->garages[i], arg1);
        printf("REMOVED FROM %s\n", campus->garages[i]->garage_name);
      } else {
        printf("NOT FOUND IN CAMPUS\n");
      }
    }
  }
}

void freeAll(Campus *campus) {
  int i;
  // freeing up all the garages
  for (i = 0; i < (campus->total_garages); i++) {
    removeGarage(campus, campus->garages[i]->garage_name);
    printf("freed garage[%d]\n", i);
  }
  free(campus->garages);
  // freeing up all the vehicles
  for (i = 0; i < campus->total_registered_vehicles; i++) {
    free(campus->registered_vehicles[i]->license_plate);
    free(campus->registered_vehicles[i]->owner_name);
    free(campus->registered_vehicles[i]);
    printf("freed vehicle[%d]\n", i);
  }
  free(campus->registered_vehicles);
  
  free(campus);

}

// other notes:
// vehicles should only be allocated once.

int main() {

  int c = 0; // number of commands

  // creating the initial campus
  Campus *campus = createCampus(&c);

  // do the following while i is less than the amount of commands
  for (int i = 0; i < c-1; i++) {
    char command[MAXSTRING];
    char arg1[MAXSTRING];
    char arg2[MAXSTRING];
    int arg1i = 0, arg2i =  0, total = 0;
    scanf("%s", command);
    
    // longest if statement known to man since you cant use switches for strings
    if (strcmp(command, "PARK") == 0) {
      scanf("%s %s", arg1, arg2);
      // finding the car's spot in the registered vehicle array
      while (strcmp(arg1, campus->registered_vehicles[arg1i]->license_plate) != 0) {
        arg1i++;
      }
      // finding the garage's spot in the garages array
      while (strcmp(arg2, campus->garages[arg2i]->garage_name) != 0) {
        arg2i++;
      }
      // actually parking the vehicle in my conveyer belt of a garage
      parkVehicle(campus->garages[arg2i], campus->registered_vehicles[arg1i]);
    } else if (strcmp(command, "UTILIZATION_REPORT") == 0) {
      generateGarageUtilizationReport(campus);
    } else if (strcmp(command, "RESIZE") == 0) {
      int capacity;
      scanf("%s %d", arg1, &capacity);
      // finding which garage the user wants
      int i = 0;
      while (strcmp(campus->garages[i]->garage_name, arg1) != 0) {
        i++;
      }
      resizeGarage(campus->garages[i], capacity);
    } else if (strcmp(command, "SEARCH_OWNER") == 0) {
      scanf("%s", arg1);
      displayVehiclesByOwner(campus, arg1);
    } else if (strcmp(command, "RELOCATE") == 0) {
      scanf("%s %s", arg1, arg2);
      relocateVehicle(campus, arg1, arg2);
    } else if (strcmp(command, "COUNT_TOTAL") == 0) {
      total = countTotalVehicles(campus);
      printf("%d\n", total);
    } else if (strcmp(command, "REGISTER_VEHICLE") == 0) {
      // registering the vehicle after the given command
      char license[MAXSTRING];
      char name[MAXSTRING];
      scanf("%s %s", license, name);
      registerVehicle(campus, license, name);
    }  else if (strcmp(command, "REMOVE_VEHICLE_GARAGE") == 0) {
      scanf("%s %s", arg1, arg2);
      removeVehicleGarage(campus, arg1, &arg1i);
    } else if (strcmp(command, "REMOVE_GARAGE") == 0) {
      scanf("%s", arg1);
      removeGarage(campus, arg1);
    }

  }


  // the following is me freeing up all the memory that was DMA'd
  freeAll(campus);

  return 0;
}
