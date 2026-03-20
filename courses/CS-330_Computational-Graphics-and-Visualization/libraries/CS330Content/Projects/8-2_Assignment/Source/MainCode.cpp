/*
 * 8-2 Assignment: 2D Animation with Collision Detection
 *
 * This program creates an interactive 2D animation featuring:
 * - Circles that move around the screen and collide with bricks and other circles
 * - Destructible bricks that require 3 hits and change color with each hit
 * - Reflective bricks that bounce circles in random directions
 * - Circle-to-circle collision that merges circles into larger ones
 *
 * Controls:
 * - SPACE: Spawn a new circle with random color
 * - ESC: Exit the program
 */

#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <cmath>  // For sqrt() function used in circle collision detection

using namespace std;

// Constant for converting degrees to radians
const float DEG2RAD = 3.14159 / 180;

// Function prototypes
void processInput(GLFWwindow* window);

// Enumerations for brick types and states
enum BRICKTYPE { REFLECTIVE, DESTRUCTABLE };
enum ONOFF { ON, OFF };

class Brick
{
public:
	float red, green, blue;
	float x, y, width;
	BRICKTYPE brick_type;
	ONOFF onoff;

	// Health system for destructible bricks
	int max_health;
	int current_health;

	Brick(BRICKTYPE bt, float xx, float yy, float ww, float rr, float gg, float bb)
	{
		brick_type = bt;
		x = xx;
		y = yy;
		width = ww;
		red = rr;
		green = gg;
		blue = bb;
		onoff = ON;

		// Initialize health based on brick type
		if (brick_type == DESTRUCTABLE)
		{
			max_health = 3;  // Destructible bricks require 3 hits
			current_health = 3;
		}
		else
		{
			max_health = 1;  // Reflective bricks don't use health
			current_health = 1;
		}
	};

	// Handle brick being hit - reduces health and updates color
	void TakeDamage()
	{
		if (brick_type == DESTRUCTABLE && onoff == ON)
		{
			current_health--;

			// Update color based on remaining health
			if (current_health == 2)
			{
				// First hit: change to yellow
				red = 1.0f;
				green = 1.0f;
				blue = 0.0f;
			}
			else if (current_health == 1)
			{
				// Second hit: change to orange
				red = 1.0f;
				green = 0.5f;
				blue = 0.0f;
			}
			else if (current_health <= 0)
			{
				// Third hit: brick is destroyed
				onoff = OFF;
			}
		}
	}

	void drawBrick()
	{
		if (onoff == ON)
		{
			double halfside = width / 2;

			glColor3d(red, green, blue);
			glBegin(GL_POLYGON);

			glVertex2d(x + halfside, y + halfside);
			glVertex2d(x + halfside, y - halfside);
			glVertex2d(x - halfside, y - halfside);
			glVertex2d(x - halfside, y + halfside);

			glEnd();
		}
	}
};


/*
 * Circle class - Represents a moving circle in the animation
 * Handles movement, collision detection with bricks and other circles,
 * and merging behavior when circles collide
 */
class Circle
{
public:
	// Color properties (RGB values 0.0 to 1.0)
	float red, green, blue;

	// Position and size
	float radius;
	float x;
	float y;

	// Movement properties
	float speed = 0.03;
	int direction; // 1=up 2=right 3=down 4=left 5=up-right 6=up-left 7=down-right 8=down-left

	// Constructor: Initialize circle with position, direction, size, and color
	Circle(double xx, double yy, double rr, int dir, float rad, float r, float g, float b)
	{
		x = xx;
		y = yy;
		radius = rr;
		red = r;
		green = g;
		blue = b;
		radius = rad;
		direction = dir;
	}

	// Check collision between circle and brick
	void CheckCollision(Brick* brk)
	{
		if (brk->onoff == OFF) return;  // Skip destroyed bricks

		// Check if circle is within brick boundaries
		if ((x > brk->x - brk->width && x <= brk->x + brk->width) &&
		    (y > brk->y - brk->width && y <= brk->y + brk->width))
		{
			if (brk->brick_type == REFLECTIVE)
			{
				// Reflective bricks bounce the circle in a random direction
				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;
			}
			else if (brk->brick_type == DESTRUCTABLE)
			{
				// Destructible bricks take damage and change color
				brk->TakeDamage();
				direction = GetRandomDirection();  // Bounce circle on hit
			}
		}
	}

	int GetRandomDirection()
	{
		return (rand() % 8) + 1;
	}

	// Check if this circle is colliding with another circle
	bool IsCollidingWith(Circle& other)
	{
		// Calculate distance between circle centers
		float dx = x - other.x;
		float dy = y - other.y;
		float distance = sqrt(dx * dx + dy * dy);

		// Circles collide if distance is less than sum of radii
		return distance < (radius + other.radius);
	}

	// Merge this circle with another circle
	void MergeWith(Circle& other)
	{
		// Calculate midpoint between the two circles
		x = (x + other.x) / 2.0f;
		y = (y + other.y) / 2.0f;

		// Calculate new radius based on combined area
		// Area = π * r^2, so combined area = π * (r1^2 + r2^2)
		// New radius = sqrt(r1^2 + r2^2)
		float combinedArea = (radius * radius) + (other.radius * other.radius);
		radius = sqrt(combinedArea);

		// Blend colors (average the RGB values)
		red = (red + other.red) / 2.0f;
		green = (green + other.green) / 2.0f;
		blue = (blue + other.blue) / 2.0f;

		// Keep the original circle's direction
		// Speed remains the same
	}

	// Move the circle one step in its current direction
	// Bounces off walls by changing to a random direction
	void MoveOneStep()
	{
		// Move up (directions: up, up-right, up-left)
		if (direction == 1 || direction == 5 || direction == 6)
		{
			if (y > -1 + radius)
			{
				y -= speed;
			}
			else
			{
				direction = GetRandomDirection();  // Bounce off top wall
			}
		}

		// Move right (directions: right, up-right, down-right)
		if (direction == 2 || direction == 5 || direction == 7)
		{
			if (x < 1 - radius)
			{
				x += speed;
			}
			else
			{
				direction = GetRandomDirection();  // Bounce off right wall
			}
		}

		// Move down (directions: down, down-right, down-left)
		if (direction == 3 || direction == 7 || direction == 8)
		{
			if (y < 1 - radius)
			{
				y += speed;
			}
			else
			{
				direction = GetRandomDirection();  // Bounce off bottom wall
			}
		}

		// Move left (directions: left, up-left, down-left)
		if (direction == 4 || direction == 6 || direction == 8)
		{
			if (x > -1 + radius)
			{
				x -= speed;
			}
			else
			{
				direction = GetRandomDirection();  // Bounce off left wall
			}
		}
	}

	// Render the circle using OpenGL
	void DrawCircle()
	{
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);
		// Draw circle using 360 vertices (one per degree)
		for (int i = 0; i < 360; i++)
		{
			float degInRad = i * DEG2RAD;
			glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
		}
		glEnd();
	}
};


// Global vector to store all active circles in the world
vector<Circle> world;


int main(void)
{
	// Seed random number generator for random colors and directions
	srand(time(NULL));

	// Initialize GLFW library
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// Set OpenGL version hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Create window
	GLFWwindow* window = glfwCreateWindow(480, 480, "8-2 Assignment", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Create bricks - mix of reflective and destructible types
	// Format: Brick(type, x, y, width, red, green, blue)
	Brick brick(REFLECTIVE, 0.5, -0.33, 0.2, 1, 1, 0);          // Yellow reflective
	Brick brick2(DESTRUCTABLE, -0.5, 0.33, 0.2, 0, 1, 0);       // Green destructible (3 hits)
	Brick brick3(DESTRUCTABLE, -0.5, -0.33, 0.2, 0, 1, 1);      // Cyan destructible (3 hits)
	Brick brick4(REFLECTIVE, 0, 0, 0.2, 1, 0.5, 0.5);           // Pink reflective

	// Main game loop
	while (!glfwWindowShouldClose(window))
	{
		// Setup viewport
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		// Process keyboard input
		processInput(window);

		// Check for circle-to-circle collisions and merge them
		for (int i = 0; i < world.size(); i++)
		{
			for (int j = i + 1; j < world.size(); j++)
			{
				if (world[i].IsCollidingWith(world[j]))
				{
					// Merge circle j into circle i
					world[i].MergeWith(world[j]);

					// Remove circle j from the world
					world.erase(world.begin() + j);
					j--;  // Adjust index after removal
				}
			}
		}

		// Movement and brick collision detection
		for (int i = 0; i < world.size(); i++)
		{
			world[i].CheckCollision(&brick);
			world[i].CheckCollision(&brick2);
			world[i].CheckCollision(&brick3);
			world[i].CheckCollision(&brick4);
			world[i].MoveOneStep();
			world[i].DrawCircle();
		}

		// Draw all bricks
		brick.drawBrick();
		brick2.drawBrick();
		brick3.drawBrick();
		brick4.drawBrick();

		// Swap buffers and poll for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup and exit
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


/*
 * Process keyboard input
 * ESC - Close the window
 * SPACE - Spawn a new circle with random color at the center
 */
void processInput(GLFWwindow* window)
{
	// ESC key - exit program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// SPACE key - spawn new circle
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		// Generate random RGB color values
		double r, g, b;
		r = rand() / 10000.0;
		g = rand() / 10000.0;
		b = rand() / 10000.0;

		// Create new circle at center (0,0) moving right with radius 0.05
		Circle B(0, 0, 0.02, 2, 0.05, r, g, b);
		world.push_back(B);
	}
}