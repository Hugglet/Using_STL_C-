#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    int priority; 
    int duration; 
};

// Функция вывода массива
void outputMas(map<int, int>& nums) {
    for (const auto& element : nums)
        cout << "Ключ: " << element.first << " Значение:" << element.second << endl;
    cout << endl;
}

// Функция произведения положительных элементов массива
int compositionElems(map<int, int>& nums, int n) {
    int multiple = 1;
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            multiple *= nums[i];
        }
    }
    return multiple;
}

// Функция суммы элементов массива, расположенных до минимального элемента
int sumElems(map<int, int>& nums) {
    if (nums.empty()) return 0; // Проверка на пустоту map
    int sum = 0;
    auto min_it = min_element(nums.begin(), nums.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second; // Сравнение по значениям
        });
    for (auto it = nums.begin(); it != min_it; ++it) {
        sum += it->second; // Суммирование значений
    }
    return sum;
}

// Функция сортировки элементов по чётным и нечётным местам
map<int, int> sortElems(map<int, int>& nums, int n) {
    map<int, int> sorted = nums;
    int k = n - 1;
    int p = n - 2;
    if (n % 2 == 0) {
        k = n - 2;
        p = n - 1;
    }
    for (int i = 0; i < n - 2; i += 2)
        for (int j = k; j > i; j -= 2)
            if (sorted[j] < sorted[j - 2]) {
                int t = sorted[j];
                sorted[j] = sorted[j - 2];
                sorted[j - 2] = t;
            }
    for (int i = 1; i < n - 2; i += 2)
        for (int j = p; j > i; j -= 2)
            if (sorted[j] < sorted[j - 2]) {
                int t = sorted[j];
                sorted[j] = sorted[j - 2];
                sorted[j - 2] = t;
            }
    return sorted;
}

// Генератор заданий
void taskGenerator(vector<Task>& taskList, int type, int time) {
    Task tsk;
    tsk.duration = time;
    tsk.priority = type;
    taskList.push_back(tsk);
}

// Функция для имитации работы системы
int simulateSystem(vector<Task>& tasks) {
    queue<Task> F; // Очередь для задач
    stack<Task> Stack; // Стек для приостановленных задач
    Task currentTask; // Текущее задание
    int processor = 0; // Процессор
    int tick = 0; // Время
    int timeExecution; // Время выполнения
    int taskPriority; // Приоритет
    currentTask.priority = -1;
    cout << "Задачи:" << endl;

    // Распределение задач по очередям
    for (Task& task : tasks) {
        cout << "Приоритет: " << task.priority << " Время выполнения: " << task.duration << endl;
        switch (task.priority) {
        case 0: F.push(task); break;
        }
    }

    // Обработка задач
    while (!F.empty() || !Stack.empty() || processor != 0) {
        cout << "Tick - " << tick << endl;
        cout << endl;
        tick++;

        // Вывод очереди
        cout << "Очередь:" << endl;
        cout << "F: ";
        queue<Task> outF = F;
        while (!outF.empty()) {
            cout << "( P: " << outF.front().priority << " - T: " << outF.front().duration << " ) ";
            outF.pop();
        }
        cout << endl;
        cout << "Стек: " << endl;
        cout << "S: " << endl;
        stack<Task> temp(Stack); // Создаем копию стека для вывода
        while (!temp.empty()) {
            const Task& task = temp.top();
            cout << "( P: " << task.priority << " T: " << task.duration << " ) ";
            temp.pop();
        }

        // Присвоение новой задачи
        if (!F.empty() && currentTask.priority == -1) {
            currentTask = F.front();
            F.pop();
        }

        // Проверка на приоритет и помещение в стек, если необходимо
        if (processor == 1) {
            if (timeExecution == 0) {
                processor = 0;
                cout << "Состояние процессора - свободен" << endl;
            }
            else {
                timeExecution--;
                cout << "Состояние процесссора - " << timeExecution << " тиков" << endl;
            }
        }
        else if (processor == 0) {
            // Имитация выполнения задачи
            processor = 1;
            // Здесь должен быть код для имитации времени выполнения
            timeExecution = currentTask.duration;
            taskPriority = currentTask.priority;
            cout << "Состояние процесссора - " << timeExecution << " тиков" << endl;
            currentTask.priority = -1;
        }
        else if (processor == 1 && currentTask.priority < taskPriority) {
            Task newTask;
            newTask.priority = taskPriority;
            newTask.duration = timeExecution;
            timeExecution = newTask.duration;
            taskPriority = currentTask.priority;
            Stack.push(newTask);
        }

        // Если в стеке есть задачи, проверяем, можно ли их обработать
        if (!Stack.empty() && F.empty()) {
            currentTask = Stack.top();
            Stack.pop();
            // Имитация выполнения задачи
            processor = 1;
            // Здесь должен быть код для имитации времени выполнения
            timeExecution = currentTask.duration;
            taskPriority = currentTask.priority;
            cout << "Состояние процесссора - " << timeExecution << " тиков" << endl;
        }
    }
    return tick;
}

// Функция для выполнения задания 2
void processData(vector<double>& data) {
    int n = data.size();
    // Нахождение максимального по модулю элемента массива
    double maxAbs = 0;
    for (int i = 0; i < n; ++i) {
        if (abs(data[i]) > maxAbs) {
            maxAbs = abs(data[i]);
        }
    }
    cout << "Максимальный по модулю элемент массива: " << maxAbs << endl;

    // Нахождение индексов первого и второго положительных элементов
    int firstPositiveIndex = -1;
    int secondPositiveIndex = -1;
    for (int i = 0; i < n; ++i) {
        if (data[i] > 0) {
            if (firstPositiveIndex == -1) {
                firstPositiveIndex = i;
            }
            else {
                secondPositiveIndex = i;
                break;
            }
        }
    }

    // Вычисление суммы элементов между первым и вторым положительными элементами
    double sumBetweenPositives = 0;
    if (firstPositiveIndex != -1 && secondPositiveIndex != -1) {
        for (int i = firstPositiveIndex + 1; i < secondPositiveIndex; ++i) {
            sumBetweenPositives += data[i];
        }
    }
    cout << "Сумма элементов между первым и вторым положительными элементами: " << sumBetweenPositives << endl;

    // Преобразование массива: перемещение нулевых элементов в конец
    int nonZeroIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (data[i] != 0) {
            swap(data[i], data[nonZeroIndex]);
            nonZeroIndex++;
        }
    }

    // Вывод массива после преобразования
    cout << "Массив после преобразования (нулевые элементы в конце): ";
    for (int i = 0; i < n; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    // Пример задач
    int x, time;
    vector<Task> tasks;
    map<int, int> data;
    do {
        cout << "1 - Создать задачу: " << endl;
        cout << "2 - Запустить систему: " << endl;
        cout << "3 - Сгенерировать 5 случайных задач: " << endl;
        cout << "4 - Выполнить действия из задачи 2: " << endl;
        cout << "0 - Выход" << endl;
        cin >> x;
        switch (x) {
        case 1:
            int type, time;
            cout << "Введите тип задачи (0, 1 или 2): ";
            cin >> type;
            cout << "Введите время выполнения задачи: ";
            cin >> time;
            data[type] = time;
            taskGenerator(tasks, type, time);
            break;
        case 2: {
            time = simulateSystem(tasks);
            data[3] = time;
            break;
        }
        case 3: {
            for (int i = 0; i < 5; i++) {
                taskGenerator(tasks, 0 + rand() % 3, 1 + rand() % 5);
                data[0 + rand() % 3] = 1 + rand() % 5;
            }
            break;
        }
        case 4: {
            // Создаем вектор из значений map
            vector<double> values;
            for (const auto& pair : data) {
                values.push_back(pair.second);
            }
            // Передаем вектор в функцию processData
            processData(values);
            break;
        }
        }
    } while (x != 0);
    return 0;
}
