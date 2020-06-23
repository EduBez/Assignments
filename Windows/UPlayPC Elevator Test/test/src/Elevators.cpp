#include "MessageBus.h"

#include "Elevators.h"

Elevators::Elevators()
{
}

void
Elevators::Start()
{
	REGISTER_ELEVATOR(MessageElevatorCall,			Elevators::OnMessageElevatorCall);
	REGISTER_ELEVATOR(MessageElevatorStep,			Elevators::OnMessageElevatorStep);
	REGISTER_ELEVATOR(MessageElevatorRequest,		Elevators::OnMessageElevatorRequest);

	myElevators.push_back(Elevator{1, 10, 6, Direction::Down});

	{
		MessageElevatorStep message;
		SEND_TO_ELEVATORS(message);
	}

	{
		MessageElevatorReady message;
		SEND_TO_HUMANS(message);
	}
}

static inline int
Distance(unsigned int elevator_floor,
         unsigned int elevator_floor_size,
         Direction elevator_direction,
         unsigned int human_floor,
         Direction human_direction)
{
    // Heuristic approach
    int numOfFloors = -1;

    // Human is going UP
    if (human_direction == Direction::Up)
    {
        // Elevator going UP
        // BELOW or on the SAME FLOOR as the Human
        if (elevator_direction == Direction::Up &&
            elevator_floor     <= human_floor)
        {
            int numOfFloors = abs(static_cast<int>(elevator_floor) - static_cast<int>(human_floor));
        }
        // Elevator going UP
        // ABOVE the FLOOR of the Human
        else if (elevator_direction == Direction::Up &&
                 elevator_floor      > human_floor)
        {
            int numOfFloors = abs(
                (static_cast<int>(elevator_floor_size) - static_cast<int>(elevator_floor)) +
                (static_cast<int>(elevator_floor_size) + static_cast<int>(human_floor))
            );
        }
        // Elevator going DOWN
        else if (elevator_direction == Direction::Down)
        {
            int numOfFloors = abs(static_cast<int>(elevator_floor) - 1);
        }
    }
    // Human is going DOWN
    else if (human_direction == Direction::Down)
    {
        // Elevator going DOWN
        // ABOVE or on the same FLOOR as the Human
        if (elevator_direction == Direction::Down &&
            elevator_floor     >= human_floor)
        {
            int numOfFloors = abs(static_cast<int>(elevator_floor) - static_cast<int>(human_floor));
        }
        // Elevator going DOWN
        // BELOW the FLOOR of the Human
        else if (elevator_direction == Direction::Down &&
                 elevator_floor      < human_floor)
        {
            int numOfFloors = abs(
                ((static_cast<int>(elevator_floor) - 1) + (static_cast<int>(elevator_floor_size))) +
                 (static_cast<int>(elevator_floor_size) - static_cast<int>(human_floor))
            );
        }
        // Elevator going UP
        else if (elevator_direction == Direction::Up)
        {
            int numOfFloors = abs(
                (static_cast<int>(elevator_floor_size) - static_cast<int>(elevator_floor)) +
                (static_cast<int>(elevator_floor_size) - static_cast<int>(human_floor))
            );
        }
    }
    return numOfFloors;
}

static inline int Distance(const Elevator& e, const MessageElevatorCall m)
{
    return Distance(
        e.CurrentFloor(), e.FloorSize(), e.CurrentDirection(),
        m.myFloor, m.myDirection
    );
}

void
Elevators::OnMessageElevatorCall(
	const MessageElevatorCall&				aMessage)
{
    // Implement me!

    Elevator& my_elevator = myElevators[0];
    int min_dist = Distance(my_elevator, aMessage);

    for (size_t i = 1; i < myElevators.size(); ++i)
    {
        Elevator& elevator = myElevators[i];
        int delta = Distance(elevator, aMessage);

        if (delta < min_dist)
        {
            min_dist = delta;
            my_elevator = elevator;
        }
    }

    my_elevator.SelectFloor(aMessage.myFloor);
}

void
Elevators::OnMessageElevatorRequest(
	const MessageElevatorRequest&			aMessage)
{
    // Implement me!

    unsigned int id = aMessage.myElevatorId;
    
    auto iter = std::find_if(myElevators.begin(), myElevators.end(),
                             [id](Elevator& elevator) {return elevator.Id() == id;});

    if (iter != myElevators.end()) {
        iter->SelectFloor(aMessage.myFloor);
    }
    
    // Failed - elvator not found
}

void
Elevators::OnMessageElevatorStep(
	const MessageElevatorStep&				aMessage)
{
	Log("[Elevators] Step");

	for (auto& elevator : myElevators)
	{
		elevator.Step();
	}

	MessageElevatorStep message;
	SEND_TO_ELEVATORS(message);
}