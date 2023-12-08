#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct Customer
{
	uint32_t money;
	uint32_t time;
	bool served;
};

bool compare_customer_money(Customer customer1, Customer customer2)
{
	if (customer1.time < customer2.time) return true;
	if (customer1.time > customer2.time) return false;

	return (customer1.money > customer2.money);
}

void bank_queue()
{
	uint32_t customer_count = 0;
	uint32_t time_until_closing = 0;

	std::cin >> customer_count;
	std::cin >> time_until_closing;


	std::vector<Customer> customers(customer_count, { 0, 0, false });

	for (uint32_t i = 0; i < customer_count; ++i)
	{
		std::cin >> customers[i].money;
		std::cin >> customers[i].time;
	}


	uint32_t total_money = 0;

	for (uint32_t time = 0; time < time_until_closing; ++time)
	{
		uint32_t max_money = 0;
		uint32_t index = -1;

		for (uint32_t i = 0; i < customer_count; ++i)
		{
			Customer& customer = customers[i];

			
			if (time <= customer.time && customer.served == false)
			{
				uint32_t max_next_money = 0;
				uint32_t next_time = time + 1;


				for (uint32_t j = 0; j < customer_count; ++j)
				{
					Customer& next_customer = customers[j];

					if (i != j && next_time <= next_customer.time && next_customer.served == false)
					{
						uint32_t money = next_customer.money;

						if (money > max_next_money)
						{
							max_next_money = money;
						}
					}
				}


				uint32_t money = customer.money + max_next_money;

				if (money > max_money)
				{
					max_money = money;
					index = i;
				}
			}
		}

		if (index != -1)
		{
			Customer& customer = customers[index];

			total_money += customer.money;
			customer.served = true;
		}
	}


	std::cout << total_money;
}


struct Car
{
	int weight;
	int heavier_cars_count;
	int lighter_cars_count;
};

bool compare_car_weights(Car car1, Car car2)
{
	return (car1.weight < car2.weight);
}

void train_sorting()
{
	int car_count = 0;

	std::cin >> car_count;


	if (car_count == 0)
	{
		std::cout << car_count;

		return;
	}


	std::vector<Car> cars(car_count, { 0, 0, 0 });

	for (int i = 0; i < car_count; ++i)
	{
		std::cin >> cars[i].weight;
	}


	std::vector<Car> sorted_cars = cars;

	std::sort(sorted_cars.begin(), sorted_cars.end(), &compare_car_weights);


	for (int i = 0; i < car_count; ++i)
	{
		Car& car = cars[i];


		int sorted_car_index = -1;

		for (int j = 0; j < car_count; ++j)
		{
			if (car.weight == sorted_cars[j].weight)
			{
				sorted_car_index = j;
				break;
			}
		}


		int car_index = 0;

		car_index = i + 1;
		int ascending_index = sorted_car_index + 1;

		while(car_index < car_count && ascending_index < car_count)
		{
			int car_weight = cars[car_index].weight;
			int sorted_car_weight = sorted_cars[ascending_index].weight;

			if (car_weight == sorted_car_weight)
			{
				++car.heavier_cars_count;
				++ascending_index;
			}

			++car_index;
		}


		car_index = i + 1;
		int descending_index = sorted_car_index - 1;

		while (car_index < car_count && descending_index >= 0)
		{
			int car_weight = cars[car_index].weight;
			int sorted_car_weight = sorted_cars[descending_index].weight;

			if (car_weight == sorted_car_weight)
			{
				++car.lighter_cars_count;
				--descending_index;
			}

			++car_index;
		}
	}


	int initial_value = 20000;
	int back_weight = initial_value;
	int front_weight = -initial_value;
	int weight_count = 1;
	int index = 0;


	int initial_index = -1;
	int max_places = -1;

	for (int i = 0; i < car_count; ++i)
	{
		Car car = cars[i];

		int front_places = car.heavier_cars_count;
		int back_places = car.lighter_cars_count;

		int places = front_places + back_places;


		if (places > max_places)
		{
			initial_index = i;
			max_places = places;
		}
	}

	front_weight = cars[initial_index].weight;
	back_weight = cars[initial_index].weight;


	index = 0;

	while(index < car_count)
	{
		int next_front_car = -1;
		int max_front_places = -1;

		for (int j = index; j < car_count; ++j)
		{
			Car car = cars[j];

			if (car.weight > front_weight)
			{
				int front_places = car.heavier_cars_count;

				if (front_places > max_front_places)
				{
					next_front_car = j;
					max_front_places = front_places;
				}
			}
		}

		if (next_front_car == -1)
		{
			break;
		}
		else
		{
			index = next_front_car + 1;
			front_weight = cars[next_front_car].weight;
			++weight_count;
		}
	}


	index = 0;

	while (index < car_count)
	{
		int next_back_car = -1;
		int max_back_places = -1;

		for (int j = index; j < car_count; ++j)
		{
			Car car = cars[j];

			if (car.weight < back_weight)
			{
				int back_places = car.lighter_cars_count;

				if (back_places > max_back_places)
				{
					next_back_car = j;
					max_back_places = back_places;
				}
			}
		}

		if (next_back_car == -1)
		{
			break;
		}
		else
		{
			index = next_back_car + 1;
			back_weight = cars[next_back_car].weight;
			++weight_count;
		}
	}


	std::cout << weight_count;
}

int main()
{
	//bank_queue();
	train_sorting();

	while (true);
}