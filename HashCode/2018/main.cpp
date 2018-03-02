#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t s32;
typedef int64_t s64;
typedef uint32_t u32;
typedef uint64_t u64;

#define Max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct
{
    s32 Row, Column;
} position;

typedef struct
{
    position Start, End;
    u64 EarliestTime, LastTime;
    u64 TimeNeeded;
    u32 AssignedTo;
} ride;

typedef struct
{
    position Position;
    u64 TimeAvailable;
    u32 NumberOfAssignedRides;
    u32 AssignedRidesIndex[1000];
} car;

ride Rides[10000];
car Cars[1000];
car *AvailableCarList[1000];

static inline s32 CalculateDistance(position Pos1, position Pos2)
{
    return (abs(Pos1.Row - Pos2.Row) + abs(Pos1.Column - Pos2.Column));
}

int main(int Argc, char *Argv[])
{
    if(Argc < 2)
    {
        exit(-1);
    }
    FILE *Input = fopen(Argv[1], "r");

    u64 NumberOfRows, NumberOfColumns, FleetSize, NumberOfRides, Bonus, NumberOfSteps;
    fscanf(Input, "%lu %lu %lu %lu %lu %lu", &NumberOfRows, &NumberOfColumns, &FleetSize, &NumberOfRides,
           &Bonus, &NumberOfSteps);

    for(u32 Index = 0; Index < NumberOfRides; ++Index)
    {
        ride *Ride = Rides + Index;

        fscanf(Input, "%d %d %d %d %lu %lu",
               &Ride->Start.Row, &Ride->Start.Column, &Ride->End.Row,
               &Ride->End.Column, &Ride->EarliestTime, &Ride->LastTime);

        Ride->TimeNeeded = CalculateDistance(Ride->Start, Ride->End) + 1;
        Ride->AssignedTo = -1;
    }

    for(u32 i = 0; i < FleetSize; ++i)
    {
        AvailableCarList[i] = Cars + i;
    }

    int NextIndex = 0;
    while(NextIndex < FleetSize && AvailableCarList[NextIndex]->TimeAvailable < NumberOfSteps-1)
    {
        car *Car = AvailableCarList[0];
        u32 CarIndex = Car - Cars;

        bool Done = false;
        u64 BestStartTime = UINT64_MAX;
        s32 ChosenRide = -1;
        for(s32 RideIndex = 0; RideIndex < NumberOfRides && !Done; ++RideIndex)
        {
            ride *Ride = Rides + RideIndex;
            if(Ride->AssignedTo != -1)
            {
                continue;
            }

            u32 Distance = CalculateDistance(Car->Position, Ride->Start);
            u32 StartTime = Max(Car->TimeAvailable+Distance, Ride->EarliestTime);

            if(StartTime + Ride->TimeNeeded <= Ride->LastTime && StartTime < BestStartTime)
            {
                BestStartTime = StartTime;
                ChosenRide = RideIndex;
            }
        }
        if(ChosenRide != -1)
        {
            ride *Ride = Rides + ChosenRide;
            u32 Distance = CalculateDistance(Car->Position, Ride->Start);
            u32 StartTime = Max(Car->TimeAvailable+Distance, Ride->EarliestTime);
            Ride->AssignedTo = CarIndex;
            Car->TimeAvailable = StartTime + Ride->TimeNeeded;
            Car->Position = Ride->End;
            Car->AssignedRidesIndex[Car->NumberOfAssignedRides++] = ChosenRide;
            Done = true;
            for(s32 CarIterator = FleetSize-1; CarIterator >= 0; --CarIterator)
            {
                if(AvailableCarList[CarIterator]->TimeAvailable < Car->TimeAvailable)
                {
                    memmove(&AvailableCarList[0], &AvailableCarList[1], sizeof(car*)*CarIterator);
                    AvailableCarList[CarIterator] = Car;
                    break;
                }
            }
        }
        if(!Done)
        {
            ++NextIndex;
        }
    }

    for(u32 CarIndex = 0; CarIndex < FleetSize; ++CarIndex)
    {
        car *Car = Cars+CarIndex;
        printf("%d ", Car->NumberOfAssignedRides);
        for(int Index = 0; Index < Car->NumberOfAssignedRides; ++Index)
        {
            printf("%d ", Car->AssignedRidesIndex[Index]);
        }

        printf("\n");
    }
}
