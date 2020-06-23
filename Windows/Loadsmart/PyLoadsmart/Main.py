import os

from Loadsmart import CreateAssociation
from Loadsmart import OptimalMapping
from Parser import ParseFile


# Main Entry Point
def main():
    # For simplicity, no exception error handling is being implemented
    
    # The 'csv' data file names must be; 'cargo.csv' and 'trucks.csv'
    # The data files must reside in the same directory as the executable
    
    # Get the application directory
    path = os.path.dirname(os.path.abspath(__file__))
    
    cargo = path + r'/data/cargo.csv'
    truck = path + r'/data/trucks.csv'
    
    # Parse each file according to its type
    cargos = ParseFile(cargo, 'Cargo')
    trucks = ParseFile(truck, 'Trucks')
    
    # Create the collection containing the 'Cargos-Trucks' association
    mmp = CreateAssociation(cargos, trucks)
    
    # Discover and store the optimal truck for each possible cargo delivery
    optimal = OptimalMapping(cargos, mmp)
    
    # Display the result
    for item in sorted(optimal.items()):
        # Unpack first tuple
        product, val = item
        # Unpack second tuple
        truck, distance = val
        print('{:<40} {:<40} {:10.2f}'.format(product, truck, distance))


# Execute Main Entry Point
if __name__ == "__main__":
    main()
