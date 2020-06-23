#include "Elevator.h"
#include "MessageBus.h"

#include "Elevators.h"

Elevator::Elevator(
	const unsigned int			aId,
	const unsigned int			aFloorCount)
	: myId(aId)
	, myFloorCount(aFloorCount)
	, myCurrentFloor(1)
	, myCurrentDirection(Direction::Up)
{
	Log("[Elevator]", myId, "Created", ToString());
}

Elevator::Elevator(
	const unsigned int		aId,
	const unsigned int		aFloorCount,
	const unsigned int		aCurrentFloor,
	const Direction			aDirection)
	: myId(aId)
	, myFloorCount(aFloorCount)
	, myCurrentFloor(aCurrentFloor)
	, myCurrentDirection(aDirection)
{
	Log("[Elevator]", myId, "Created", ToString());
}

static inline Direction ChangeDirection(
    unsigned int destination_floor,
    unsigned int current_floor)
{
    int delta = static_cast<int>(destination_floor) - static_cast<int>(current_floor);
    return delta > 0 ? Direction::Up : Direction::Down;
}

void
Elevator::SelectFloor(
	const unsigned int			aFloorId)
{
	// Implement me!

    bool working = HasWork();

    if (!working && (aFloorId != myCurrentFloor)) {
        myCurrentDirection = ChangeDirection(aFloorId, myCurrentFloor);
    }
    mySelectedFloors.insert(aFloorId);
}

unsigned int
Elevator::CurrentFloor() const
{
	return myCurrentFloor;
}

Direction
Elevator::CurrentDirection() const
{
	return myCurrentDirection;
}

unsigned int
Elevator::FloorSize() const
{
	return myFloorCount;
}

bool
Elevator::HasWork() const
{
	// Implement me!

    bool working = mySelectedFloors.size() > 0;
    return working;
}

void
Elevator::Step()
{
	// Implement me!

    if (HasWork())
    {
        if (mySelectedFloors.find(myCurrentFloor) == mySelectedFloors.end())
        {
            if (myCurrentFloor == 1) {
                myCurrentDirection = Up;
            }
            else if (myCurrentFloor == myFloorCount) {
                myCurrentDirection = Down;
            }

            switch (myCurrentDirection)
            {
                case Up:
                    ++myCurrentFloor;
                    break;
                case Down:
                    --myCurrentFloor;
                    break;
                default:
                    // fail
                    break;
            }
        }
        
        MessageElevatorArrived message{myId, myCurrentFloor};
        SEND_TO_HUMANS(message);

        mySelectedFloors.erase(myCurrentFloor);
    }
}

unsigned int
Elevator::Id() const
{
	return myId;
}

std::string
Elevator::ToString() const
{
	return "- State: " 
		+ std::to_string(myCurrentFloor) 
		+ "/" 
		+ std::to_string(myFloorCount) 
		+ " " 
		+ ::ToString(myCurrentDirection);
}