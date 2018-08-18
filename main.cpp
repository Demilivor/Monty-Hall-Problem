/*
 * Copyright (c) 2017 Alexey Gerasimchuk (Demilivor@mail.ru)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <deque>
#include <algorithm>

#include <ctime>
#include <cstdlib>

// Count of doors, that player could select
static constexpr size_t DOORS_COUNT = 3;

std::deque<int> GetDoors()
{
  std::deque<int> doors;
  for ( size_t door = 0;  door < DOORS_COUNT; ++door )
  {
      doors.emplace_back( door );
  }

  return doors;
}

bool ChangeDoor()
{
    // Possible doors to select from( 0...DOORS_COUNT )
    std::deque<int> doors = GetDoors();

    // Select a door with a prize from all doors
    int doorWithPrize = doors[(std::rand() % doors.size())];

    // Select player door
    int firstChoice = doors[(std::rand() % doors.size())];

    // Remove selected and prize door from all doors
    doors.erase( std::find(doors.begin(), doors.end(), firstChoice) );
    if ( firstChoice != doorWithPrize )
    {
        // Host know which door is door with prize, remove it if player
        // selected other door
        doors.erase( std::find(doors.begin(), doors.end(), doorWithPrize) );
    }

    // Now doors contain only doors that host could open with no prize.
    // Remove random door without prize
    doors.erase( doors.begin() + ( std::rand() % doors.size()) );
    if ( firstChoice != doorWithPrize )
    {
        // if player select non prize door, this door still could be selected
        doors.emplace_back( doorWithPrize );
    }

    // Select player door
    int secondChoice = doors[(std::rand() % doors.size())];

    // If player door equal to prize door, player got the prize
    return doorWithPrize == secondChoice;
}

bool DontChangeDoor()
{
  // Possible doors to select from( 0...DOORS_COUNT )
  std::deque<int> doors = GetDoors();

  // Select a door with a prize from all doors
  int doorWithPrize = doors[(std::rand() % DOORS_COUNT)];

  // Select player door
  int firstChoice = doors[(std::rand() % DOORS_COUNT)];

  // If player door equal to prize door, player got the prize
  return doorWithPrize == firstChoice;
}

int main()
{
	constexpr size_t TESTS_COUNT = 10000;

	std::srand(std::time(0));
	int guessChangeDoor = 0;
	int guessDontChangeDoor = 0;

	for (size_t i = 0; i < TESTS_COUNT; ++i)
	{
		if (ChangeDoor())
			++guessChangeDoor;
		if (DontChangeDoor())
			++guessDontChangeDoor;
	}

	std::cout << "Chanse to select a door with prize if player changes selected door"
              << guessChangeDoor * 1.0 / TESTS_COUNT
              << "\nChanse to select a door with prize if player doesn't change selected door"
              << guessDontChangeDoor * 1.0 / TESTS_COUNT << std::endl;

	return 0;
}
