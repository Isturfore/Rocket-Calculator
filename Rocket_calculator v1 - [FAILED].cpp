#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <exception>
#include <cmath>
#include <chrono>

void Single_Stage_LaunchVehicle()
{
    double Angle_Of_Horizon;
    double Max_Flight_Altitude = 0;
    double Max_Flight_Speed = 0;
    double Specific_Impulse;
    double Thrust;
    double Initial_Mass;
    double Final_Mass;
    double Second_Fuel_Mass_Consumption;
    double Acceleration_Of_Free_Fall;
    double Time_Of_Operating;


    printf("\t\t|STEP 2: Specifying The Initial Startup Parameters|.\n\n\n");



    printf("\tSTEP 2.1: Specify the acceleration of the planet's free fall (real number) [m/s^2] {0.0+} - ");
    std::cin >> Acceleration_Of_Free_Fall;
    if (Acceleration_Of_Free_Fall < 0.0)
    {
        throw std::runtime_error("Error! This argument cannot be less than 0.\n");
    }
    std::cout << std::endl;


    printf("\tSTEP 2.2: Specify the total fuel consumption of the launch vehicle (real number) [kg/s] {0.001+} - ");
    std::cin >> Second_Fuel_Mass_Consumption;
    if (Second_Fuel_Mass_Consumption < 0.001)
    {
        throw std::runtime_error("Error! This argument cannot be less than 0.001.\n");
    }
    std::cout << std::endl;


    printf("\tSTEP 2.3: Specify the total thrust of the launch vehicle (real number) [H] {0.001+} - ");
    std::cin >> Thrust;
    if (Thrust < 0.001)
    {
        throw std::runtime_error("Error! This argument cannot be less than 0.001.\n");
    }
    std::cout << std::endl;


    printf("\tSTEP 2.4: Specify the initial mass of the launch vehicle (payload + vehicle design + fuel) (real number) [kg] {0.001+} - ");
    std::cin >> Initial_Mass;
    if (Initial_Mass < 0.001)
    {
        throw std::runtime_error("Error! This argument cannot be less than 0.001.\n");
    }
    std::cout << std::endl;


    printf("\tSTEP 2.5: Specify the final mass of the launch vehicle (payload + vehicle design) (real number) [kg] {0.001+ and initial mass-} - ");
    std::cin >> Final_Mass;
    if (Final_Mass >= Initial_Mass || Final_Mass < 0.001)
    {
        throw std::runtime_error("Error! This argument cannot be less than 0.001 or more/equal then Initial_Mass.\n");
    }
    std::cout << std::endl;


    printf("\tSTEP 2.6: Specify the launch angle of the launch vehicle to the horizon (real number) [\370] {1+ and 90-} - ");
    std::cin >> Angle_Of_Horizon;
    if (Angle_Of_Horizon < 1 || Angle_Of_Horizon > 90)
    {
        throw std::runtime_error("Error! This argument cannot be less than 1 or more then 90.\n");
    }
    std::cout << std::endl;

   

    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tCalculation");
    for (int i = 0; i < 3; i++)
    {
        Sleep(300);
        printf(".");
    }

    auto start = std::chrono::high_resolution_clock::now();

    Specific_Impulse = Thrust / (Second_Fuel_Mass_Consumption * Acceleration_Of_Free_Fall);
    Time_Of_Operating = (Initial_Mass - Final_Mass) / Second_Fuel_Mass_Consumption;

    double Current_Mass = Initial_Mass;
    double Time = 0.0;
    double Delta_Time = 0.01;
    double Acceleration;

    while (Current_Mass > Final_Mass)
    {
        Acceleration = (Thrust / Current_Mass) - Acceleration_Of_Free_Fall;

        if (Acceleration < 0)
        {
            throw std::runtime_error("Error! The launch vehicle could not overcome gravity.\n");
        }

        Max_Flight_Speed += Acceleration * Delta_Time;

        Max_Flight_Altitude += Max_Flight_Speed * Delta_Time;

        Current_Mass -= Second_Fuel_Mass_Consumption * Delta_Time;
        Time += Delta_Time;
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\\|RESULTS|/\n\n\n");

    printf("\t\t\t\t\t\t\t\t\tEngine operating time: +- %.2lf s\n\n", Time_Of_Operating);
    printf("\t\t\t\t\t\t\t\t\tSpecific Impulse: +- %.2lf s\n\n", Specific_Impulse);
    printf("\t\t\t\t\t\t\t\t\tMaximum flight speed: +- %.2lf m/s\n\n", Max_Flight_Speed);
    printf("\t\t\t\t\t\t\t\t\tMaximum flight altitude: +- %.2lf m \n\n\n\n", Max_Flight_Altitude);

    printf("\t\t\t\t\t\t\tProgram execution time: %lf s\n\n\n", duration.count());
}

void Multi_Stage_LaunchVehicle()
{

}

int main()
{
    int Count_Of_Stages;

    printf("\n\n\n\t\t\t\t\t\tThis Is The \"RocketSTAT Program\", It Will Allow You To Calculate Important Data About The Flight Of Your Launch Vehicle.\n\n\n\n\n\n");
    printf("\t\t|STEP 1: Specify The Number Of Stages Of Your Launch Vehicle (Integer Number) {1+}| - ");

    std::cin >> Count_Of_Stages;
    std::cout << std::endl << std::endl << std::endl;

    if (Count_Of_Stages < 1)
    {
        throw std::runtime_error("Error! This argument cannot be less than 1.\n");
    }
    else if (Count_Of_Stages == 1)
    {
        try
        {
            Single_Stage_LaunchVehicle();
        }
        catch (const std::exception& ex)
        {
            printf("\n\n\n\n\t\t\tError: %s", ex.what());
        }
    }
    else
    {
        try
        {
            Multi_Stage_LaunchVehicle();
        }
        catch (const std::exception& ex)
        {
            printf("\n\n\n\n\t\t\tError: %s", ex.what());
        }
    }

    return 0;
}