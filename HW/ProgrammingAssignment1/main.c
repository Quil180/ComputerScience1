/* COP 3502C Assignment 1
This program is written by: Yousef Alaa Awad */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 21

// structures that I must include
typedef struct RegisteredVehicle { // for one registered vehicle
  char *license_plate;             // string for license plate
  char *owner_name;                // string for owner of vehicle
} RegisteredVehicle;

typedef struct Garage { // for one garage
  char *garage_name;    // string for name of garage
  int total_capacity;   // total capacity of garage
  int current_count;    // vehicles parked in a particular time
  RegisteredVehicle *
      *parked_vehicles; // list of parked vehicles in a particle time
} Garage;

typedef struct Campus {
  Garage **garages;                        // list of garages on campus
  int total_garages;                       // number of garages on campus
  RegisteredVehicle **registered_vehicles; // list of all registered vehicles
  int total_registered_vehicles; // total number of registered vehicles
} Campus;

// function i made (has to be placed here to work)
int findVehicleInGarage(Campus *campus, const char *license) {
  int i = 0, j = 0;
  // going through every garage to find if a vehicle is in said garage.
  for (i = 0; i < campus->total_garages; i++) {
    for (j = 0; j < campus->garages[i]->current_count; j++) {
      // comparing the current vehicle's license plate with the given license plate
      if (strcmp(license, campus->garages[i]->parked_vehicles[j]->license_plate) == 0) {
        // since the strcmp was exactly equal we found the location of the vehicle in the current garage
        return i;
      }
    }
  }
  // if the vehicle is not found, then it returns -1
  return -1; 
} // returns the garage that the vehicle is found in


// Functions I must implement
Garage *createGarage(const char *name, int capacity) {
  // creates a new garage and initializes it

  // creating the garage via DMA
  Garage *garage = (Garage *)calloc(1, sizeof(Garage)); 
  // creating the name of the string via DMA
  garage->garage_name = (char *)calloc(strlen(name) + 1, sizeof(char)); 
  // putting the name of the garage into the structure
  strcpy(garage->garage_name, name);
  // giving it the total capacity
  garage->total_capacity = capacity;
  // creating the array of parked vehicles with size of the max capacity
  garage->parked_vehicles = (RegisteredVehicle **)calloc(capacity, sizeof(RegisteredVehicle)); 
  // initializing the current capacity of the garage to be 0
  garage->current_count = 0; 

  return garage;
};


RegisteredVehicle *createRegisteredVehicle(const char *license, const char *owner) {
  // create a new vehicle registry
  RegisteredVehicle *vehicle = (RegisteredVehicle *)calloc(1, sizeof(RegisteredVehicle));

  // allocating the memory for both the name and license plate
  vehicle->owner_name = (char *)calloc(strlen(owner) + 1, sizeof(char));
  vehicle->license_plate = (char *)calloc(strlen(license) + 1, sizeof(char));
  // copying the values of the license and owner to the vehicle registrigation
  strcpy(vehicle->owner_name, owner);
  strcpy(vehicle->license_plate, license);

  // returning the newly made vehicle's pointer
  return vehicle;
};

void registerVehicle(Campus *campus, const char *license, const char *owner) {
  // register a new vehicle on campus
  campus->total_registered_vehicles += 1;
  // allocates the memory for the vehicle
  campus->registered_vehicles = (RegisteredVehicle **)realloc(campus->registered_vehicles, campus->total_registered_vehicles * sizeof(RegisteredVehicle));
  campus->registered_vehicles[campus->total_registered_vehicles - 1] = createRegisteredVehicle(license, owner);
}

void parkVehicle(Garage *garage, RegisteredVehicle *vehicle) {
  // park a vehicle at a garage. If full, print FULL, other park and print PARKED
  // checking if the garage is full
  if (garage->current_count == garage->total_capacity) {
    // the garage was found to be full
    printf("FULL\n");
  } else {
    // assuming the garage is not full and therefore parking
    garage->parked_vehicles[(garage->current_count)] = vehicle;
    garage->current_count += 1;
    printf("PARKED\n");
  }
}

int removeVehicleFromGarage(Garage *garage, const char *license) {
  // remove vehicle from a garage. Return 1 if succesful otherwise return 0
  int i = 0, j = 0;
  // find the vehicle in question
  for (i = 0; i < garage->current_count; i++) {
    if (strcmp(license, garage->parked_vehicles[i]->license_plate) == 0) {
      // since we found the vehicle to remove, exit the for loop
      break;
    }
  }
  // if the i value is, for some reason, equal to the current count, end the functions
  if (i >= garage->current_count) {
    return 0;
  }
  // remove the vehicle from the garage then lower the current count
  if (i != (garage->current_count - 1)) {
    // if the vehicle is not in the last spot of the parked vehicles
    for (j = i; j < garage->current_count; j++) {
      // move the vehicles to the right to the left.
      garage->parked_vehicles[j] = garage->parked_vehicles[j + 1];
    }
  } else {
    // assuming the vehicle is in the last spot
    garage->parked_vehicles[i] = NULL; // get rid of the vehicle
  }
  // lowering the garage's current count of parked vehicles
  garage->current_count -= 1;
  return 1;
}

RegisteredVehicle *searchVehicleByLicense(const Campus *campus, const char *license) {
  // search for vehicle by license. If found return vehicle, else return NULL
  int i = 0;
  // searching for the vehicle with the same license plate
  while (strcmp(license, campus->registered_vehicles[i]->license_plate) != 0) {
    i++;
    if (i >= campus->total_registered_vehicles) {
      // the vehicle was not found and therefore we return NULL
      return NULL;
    }
  }
  return campus->registered_vehicles[i];
};

int countTotalVehicles(const Campus *campus) {
  // returns number of vehicles parked on campus
  int total = 0;
  for (int i = 0; i < campus->total_garages; i++) {
    // adding the garage's currently parked vehicles to a total counter
    total += campus->garages[i]->current_count;
  }
  return total;
}

int resizeGarage(Garage *garage, int new_capacity) {
  // resizes garage to new capacity. If capacity smaller than vehicles parked,
  // print FAIL. TOO SMALL TO ACCOMODATE EXISTING VEHICLES. Return 1 or 0
  // depending on if successful or not.
  if (garage->current_count > new_capacity) {
    // the garage has too many cars
    printf("FAIL. TOO SMALL TO ACCOMMODATE EXISTING VEHICLES.\n");
    return 0;
  } else {
    // assuming the garage can be resized without kicking out any cars
    // reallocate the memory associated with the garage
    garage->parked_vehicles = (RegisteredVehicle **)realloc(garage->parked_vehicles, new_capacity * sizeof(RegisteredVehicle));
    garage->total_capacity = new_capacity;
    printf("SUCCESS\n");
    return 1;
  }
}

int relocateVehicle(Campus *campus, const char *license, const char *target_garage_name) {
  // relocate vehicle to another garage. If
  // garage not found, print [G] NOT FOUND.
  // If garage full, print [G] IS FULL.
  // Return 1 or 0 if successful or not.
  RegisteredVehicle *temp = searchVehicleByLicense(campus, license);
  int garagefound = -1, carfound = -1;
  // seeing if the target garage exists
  for (int i = 0; i < campus->total_garages; i++) {
    if (strcmp(target_garage_name, campus->garages[i]->garage_name) == 0) {
      // the garage was found!
      garagefound = i;
    }
  }
  // check if the car is on campus to begin with
  for (int i = 0; i < campus->total_garages; i++) {
    for (int j = 0; j < campus->garages[i]->current_count; j++) {
      if (strcmp(license, campus->garages[i]->parked_vehicles[j]->license_plate) == 0) {
        // the car was found on campus!!
        carfound = j;
      }
    }
  }

  if (garagefound == -1) {
    // the garage was not found.
    printf("%s NOT FOUND.\n", target_garage_name);
    return 0;
  } else if (carfound == -1) {
    // the car was not parked on campus
    printf("%s NOT IN CAMPUS.\n", license);
    return 0;
  } else {
    // assuming the vehicle was found in a garage
    // and the target garage exists
    // remove the vehicle from the garage found in
    // find the current garage the car is parked in
    int cargarageisin = findVehicleInGarage(campus, license);
    // check if the target garage is full
    if (campus->garages[garagefound]->current_count == campus->garages[garagefound]->total_capacity) {
      printf("%s IS FULL.\n", target_garage_name);
      return 0;
    } else {
      // assuming the target garage is not full
      removeVehicleFromGarage(campus->garages[cargarageisin], license);
      // park the car in the new garage
      parkVehicle(campus->garages[garagefound], temp);
      printf("RELOCATION SUCCESSFUL.\n");
    }
  }
  // since the function got this far, we were successfull :)
  return 1;
}

void displayVehiclesByOwner(const Campus *campus, const char *owner_name) {
  int i, gi, gj;
  int vehicle_found = 0, numvehicles = 0;

  for (i = 0; i < campus->total_registered_vehicles; i++) {
    // setting vehicle_found to 0 as it has not been found in a garage yet
    vehicle_found = 0;
    if (strcmp(owner_name, campus->registered_vehicles[i]->owner_name) == 0) {
      // check if the car is in a garage
      for (int garagei = 0; garagei < campus->total_garages; garagei++) {
        for (int garagej = 0; garagej < campus->garages[garagei]->current_count; garagej++) {
          // comparing the licencse plate with the vehicles in the garage
          if (strcmp(campus->registered_vehicles[i]->license_plate, campus->garages[garagei]->parked_vehicles[garagej]->license_plate) == 0) {
            // the car was found in the garage
            numvehicles += 1;
            vehicle_found = 1;
            // setting the location of the car in the garage for later use
            gi = garagei;
            gj = garagej;
          }
        }
      }

      if (!vehicle_found) {
        // since the vehicle was found
        numvehicles += 1;
        printf("%s NOT ON CAMPUS\n",
               campus->registered_vehicles[i]->license_plate);
      } else {
        printf("%s %s\n", campus->garages[gi]->parked_vehicles[gj]->license_plate, campus->garages[gi]->garage_name);
      }
    }
  }
  if (numvehicles == 0) {
    // no vehicles were found at all by the owner given.
    printf("NO REGISTERED CAR BY THIS OWNER\n");
  }
}

int removeGarage(Campus *campus, const char *garage_name) {
  // searching for the garage
  for (int i = 0; i < campus->total_garages; i++) {
    if (strcmp(garage_name, campus->garages[i]->garage_name) == 0) {
      // remove the garage from memory
      free(campus->garages[i]->parked_vehicles);
      free(campus->garages[i]->garage_name);
      free(campus->garages[i]);

      // move the garages in the array to the left
      for (int j = i; j < campus->total_garages - 1; j++) {
        campus->garages[j] = campus->garages[j + 1];
      }
      // decrease the total garages count
      campus->total_garages -= 1;
      // print out the statement required
      printf("%s REMOVED\n", garage_name);
      return 1;
    }
  }
  // if it gets this far, then the given garage never existed
  printf("%s NOT FOUND\n", garage_name);
  return 0;
}

void generateGarageUtilizationReport(const Campus *campus) { 
  // generate a report on all garage. print the following:
  // Garage: [G], Capacity: [GC], Occupied: [GO], Utilization: [GU]%
  // After this print the name of the garage which is utilized the least.
  double utilizedi = 100.00;
  int j = 0;
  for (int i = 0; i < campus->total_garages; i++) {
    // for every garage print the following:
    printf("Garage: %s, Capacity: %d, Occupied: %d, Utilization: %0.2f%%\n", campus->garages[i]->garage_name, campus->garages[i]->total_capacity, campus->garages[i]->current_count, 100.00 * (campus->garages[i]->current_count) / (campus->garages[i]->total_capacity));
    if (utilizedi > 1.0 * (campus->garages[i]->current_count) / (campus->garages[i]->total_capacity)) {
      // log the least utilized garage
      j = i;
      // update the minimum utilization
      utilizedi = 1.0 * (campus->garages[i]->current_count) / (campus->garages[i]->total_capacity);
    }
  }
  printf("Least Utilized: %s\n", campus->garages[j]->garage_name);
}

// the following functions that I made.
Campus *
createCampus(int *c) { // the function that takes in all of the initial data
  int i = 0, j = 0, size = 0;
  char name[MAXSTRING];
  char license[MAXSTRING];
  Campus *campus = (Campus *)calloc(1, sizeof(Campus));
  // getting the amount of garages, vehicle amount at start (parked and not
  // parked), and amount of commands total
  scanf("%d", &(campus->total_garages));
  scanf("%d", &(campus->total_registered_vehicles));
  scanf("%d", c);
  campus->garages = (Garage **)calloc(campus->total_garages, sizeof(Garage)); // allocating the memory for number of garages, g.
  for (i = 0; i < campus->total_garages; i++) {
    // for every garage find its size and name
    scanf("%s %d", name, &size);
    // and then create it in the memory
    campus->garages[i] = createGarage(name, size);
  }

  campus->registered_vehicles = (RegisteredVehicle **)calloc(campus->total_registered_vehicles, sizeof(RegisteredVehicle)); // making the array of vehicles
  // creating the registry of vehicles
  for (i = 0; i < campus->total_registered_vehicles; i++) {
    // for every vehicle find its license plate and owner
    scanf("%s %s", license, name);
    // then create it in memory
    campus->registered_vehicles[i] = createRegisteredVehicle(license, name);
  }

  // return the initialized campus that we made above
  return campus;
};

void freeAll(Campus *campus) {
  int i;

  // freeing the registered vehicles of the campus
  for (i = 0; i < campus->total_registered_vehicles; i++) {
    free(campus->registered_vehicles[i]->license_plate);
    free(campus->registered_vehicles[i]->owner_name);
    free(campus->registered_vehicles[i]);
  }
  // freeing the whole registered vehicles array
  free(campus->registered_vehicles);

  // freeing the garages subitems that the createGarage structure allocates
  for (i = 0; i < campus->total_garages; i++) {
    free(campus->garages[i]->parked_vehicles);
    free(campus->garages[i]->garage_name);
    free(campus->garages[i]); 
  }
  // freeing the whole garages array
  free(campus->garages);
  // freeing the campus from memory
  free(campus);
}


// other notes:
// vehicles should only be allocated once.

int main() {

  int c = 0; // number of commands

  // creating the initial campus
  Campus *campus = createCampus(&c);

  // do the following while i is less than the amount of commands
  for (int i = 0; i < c; i++) {
    // printf("command %d\n", i);
    char command[MAXSTRING];
    char arg1[MAXSTRING];
    char arg2[MAXSTRING];
    int arg1i = 0, arg2i = 0, total = 0, i;
    scanf("%s", command);

    // longest if statement known to man since you cant use switches for strings
    if (strcmp(command, "PARK") == 0) {
      scanf("%s %s", arg1, arg2);
      // finding the car's spot in the registered vehicle array
      while (strcmp(arg1, campus->registered_vehicles[arg1i]->license_plate) != 0) {
        arg1i++;
        if (arg1i > campus->total_registered_vehicles) {
          break;
        }
      }
      // finding the garage's spot in the garages array
      while (strcmp(arg2, campus->garages[arg2i]->garage_name) != 0) {
        arg2i++;
        if (arg2i > campus->total_garages) {
          break;
        }
      }
      // actually parking the vehicle in my conveyer belt of a garage
      parkVehicle(campus->garages[arg2i], campus->registered_vehicles[arg1i]);
    } else if (strcmp(command, "UTILIZATION_REPORT") == 0) {
      generateGarageUtilizationReport(campus);
    } else if (strcmp(command, "RESIZE") == 0) {
      int capacity;
      scanf("%s %d", arg1, &capacity);
      // finding which garage the user wants
      i = 0;
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
      printf("REGISTERED\n");
    } else if (strcmp(command, "REMOVE_VEHICLE_GARAGE") == 0) {
      int foundgarage = 0;
      // arg1 is the license plate of the car we want to remove
      scanf("%s", arg1);
      // first we check if the car is on campus
      foundgarage = findVehicleInGarage(campus, arg1);
      if (foundgarage == -1) {
        printf("NOT FOUND IN CAMPUS\n");
      } else {
        int worked =
            removeVehicleFromGarage(campus->garages[foundgarage], arg1);
        if (worked) {
          printf("REMOVED FROM %s\n", campus->garages[foundgarage]->garage_name);
        }
      }
    } else if (strcmp(command, "REMOVE_GARAGE") == 0) {
      scanf("%s", arg1);
      removeGarage(campus, arg1);
    }
  }

  // the following is me freeing up all the memory that was DMA'd
  freeAll(campus);

  return 0;
}
