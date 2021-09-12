#include <iostream>
#include <vector>

/// <summary>
/// Seraphim Ivanov, 0392, 2021 year
/// Алгоритм поиска минимального пути между двумя вершинами заранее известного древесного графа
/// </summary>

struct stack // реализация стека через структуру
{
	int value;
	stack* previous;
	stack(int _value, stack* _previous = nullptr) : value(_value), previous(_previous) {};
};

int main()
{
	setlocale(LC_ALL, "rus");
	//    0          1          2          3             4             5           6          7        8      9      10   11      12       13    14         15            16           17           18        19    20    21    22    23    24    25    26    27    28    29
	std::vector<std::vector<int>> graf = { {1, 2, 3}, {0, 4, 5}, {0, 6, 7}, {0, 8, 9}, {1, 10, 11, 12}, {1, 13, 14}, {2, 15}, {2, 16, 17}, {3}, {3, 18}, {4}, {4}, {4, 19, 20}, {5}, {5}, {6, 21, 22, 23}, {7, 24, 25}, {7, 26, 27}, {9, 28, 29}, {12}, {12}, {15}, {15}, {15}, {16}, {16}, {17}, {17}, {18}, {18} };

	int track = 99;             // переменная, в кортой храним путь
	int count = 0;              // счетчик пути от исходной вершины до рассматриваемой
	int point1 = 0;             // 
	int point2 = 0;             // первая и вторая вершины
	bool visited[30] = { 0 };   // статус-массив посещенности вершины
	//std::cout << "Введите вершину №1: ";
	std::cin >> point1;
	//std::cout << "Введите вершину №2: ";
	std::cin >> point2;
	int seing = point1;
	stack* top = new stack(point1);

	while (top)  // до тех пор, пока стек не пуст - продолжаем поиск в глубину
	{
		if (top->value == point2 && count < track) //если новый пути короче старого
		{
			track = count;
		}

		seing = top->value;     // сейчас рассматриваем вершину, записанную в вершине стека 
		stack* tmp_top = top;
		top = top->previous;
		delete tmp_top;

		if (visited[seing] == 1) // если вернулись к вершине, которую уже анализировали - обход какой-то из веток завершился
								 // а значит длина пути уменьшается
		{
			count--;
		}
		else                     // иначе - движение вглубь
		{
			count++;
		}

		if (visited[seing] == 0) // если вершина встречается впервые - добавляем в стек ее соседей
		{
			for (int i = 0; i < graf.at(seing).size(); i++)
			{
				if (visited[graf.at(seing).at(i)] == 0)
				{
					tmp_top = new stack(seing, top);    // и записываем анализируемую вершину в стек, чтобы отслеживать путь "назад"
														// таким образом, когда вершиной стека снова станет эта вершина 
														// мы сможем понять, что путь надо декрементировать
					top = tmp_top;
					tmp_top = new stack(graf.at(seing).at(i), top);
					top = tmp_top;
				}
			}
		}
		visited[seing] = 1; // помечаем рассматриваемую вершину как пройденную
	}
	//Кратчайший путь между вершинами составляет
	std::cout << track << "\n";
	return 0;
}