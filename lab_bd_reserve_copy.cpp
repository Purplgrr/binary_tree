#include <iostream>

using namespace std;

int tabs = 0;// будет являться носителем значения уровня узла (+ считает количество отступов)

struct Key
{
	char Data;
	Key* LeftKey;// имя указателя, key это структура или тип ; (pointer_name)->(variable_name)
	Key* RightKey;
};
/*"Причина введения nullptr в язык С++ заключается в устранение возможных недоразумений между литералом 0 как целочисленным значением и указателем. Двойное значение литерала 0 может вызывать проблемы при некоторых обстоятельствах. */


void AddKey(int currData, Key*& currKey)
{
	if (!currKey) // если ключа(узла) нет, то создать его, добавить данные, в правый и левый узел добавить null(0) 
	{
		currKey = new Key;
		currKey->Data = currData;
		currKey->LeftKey = 0;
		currKey->RightKey = 0;
		return;
	}
	if (currKey->Data > currData) // если значение ключа меньше предыдущего ключа , то добавляем ключ влево
	{
		AddKey(currData, currKey->LeftKey);
	}
	else // если значение ключа больше предыдущего ключа , то добавляем ключ вправо
	{
		AddKey(currData, currKey->RightKey);
	};
}


void Print(Key* currKey)
{
	if (!currKey)return;
	tabs++;

	Print(currKey->RightKey);


	for (int i = 1; i < tabs; i++)
		cout << "\t";


	cout << currKey->Data << endl;
	Print(currKey->LeftKey);


	tabs--;
	return;

}

void PreOrder(Key* currKey)// Прямой обход
{
	if (!currKey) return;
	{
		cout << (currKey->Data) << " ";
		PreOrder(currKey->LeftKey);
		PreOrder(currKey->RightKey);

	}
}

void PostOrder(Key* currKey)// Обратный обход
{
	if (!currKey) return;
	{

		PostOrder(currKey->LeftKey);
		PostOrder(currKey->RightKey);
		cout << (currKey->Data) << " ";
	}
}

void InOrderUp(Key* currKey)// Симметричный обход (ЛКП)
{
	if (!currKey) return;
	{

		InOrderUp(currKey->LeftKey);
		cout << (currKey->Data) << " ";
		InOrderUp(currKey->RightKey);

	}
}

void InOrderDown(Key* currKey)// Симметричный обход (ПКЛ)
{
	if (!currKey) return;
	{
		InOrderDown(currKey->RightKey);
		cout << (currKey->Data) << " ";
		InOrderDown(currKey->LeftKey);
	}
}

void DeleteAll(Key* currKey)//очистить
{
	if (!currKey)return;
	DeleteAll(currKey->LeftKey);
	DeleteAll(currKey->RightKey);
	delete currKey;
	return;
}


int SearchMax(Key* currKey)// поиск максимального элемента
{
	int result;
	while (currKey->RightKey) {
		currKey = currKey->RightKey;

	}result = currKey->Data;
	cout << "\n" << result << endl;
	return result;
}

void DeleteKey(Key*& currKey, int currData)// Удаление максимального слева элемента
{
	if (currKey) {
		if (currData < currKey->Data)
		{
			DeleteKey(currKey->LeftKey, currData);
		}
		else if (currData > currKey->Data)
		{
			DeleteKey(currKey->RightKey, currData);
		}
		else if ((!currKey->LeftKey) && (!currKey->RightKey))// тут перестает выполнять
		{
			currKey = 0;
		}
		else if ((currKey->LeftKey) && (currKey->RightKey))
		{
			currKey->Data = SearchMax(currKey->LeftKey);
			DeleteKey(currKey->LeftKey, currKey->Data);
		}
		else if (currKey->LeftKey)
		{
			currKey = currKey->LeftKey;
		}
		else
		{
			currKey = currKey->RightKey;
		}
	}

}
//удаление



/*Key* DeleteNode(Key* currKey, int currData) {
	if (currKey == NULL)
		return currKey;

	if (currData == currKey->Data) {

		Key* tmp;
		if (currKey->RightKey == NULL)
			tmp = currKey->LeftKey;
		else {

			Key* ptr = currKey->RightKey;
			if (ptr->LeftKey == NULL) {
				ptr->LeftKey = currKey->LeftKey;
				tmp = ptr;
			}
			else {

				Key* pmin = ptr->LeftKey;
				while (pmin->LeftKey != NULL) {
					ptr = pmin;
					pmin = ptr->LeftKey;
				}
				ptr->LeftKey = pmin->RightKey;
				pmin->LeftKey = currKey->LeftKey;
				pmin->RightKey = currKey->RightKey;
				tmp = pmin;
			}
		}

		delete currKey;
		return tmp;
	}
	else if (currData < currKey->Data)
		currKey->LeftKey = DeleteNode(currKey-> LeftKey, currData);
	else
		currKey->RightKey = DeleteNode(currKey->RightKey, currData);
	return currKey;
}*/

int main()
{
	setlocale(LC_ALL, "RU");

	cout << "БИНАРНОЕ ДЕРЕВО ПОИСКА" << endl;

	Key* Root = 0;
	char  s[] = "14345878859";

	for (int i = 0; s[i]; i++)
	{
		AddKey(s[i], Root);
	}

	Print(Root);

	cout << "Прямой обход:" << endl;
	PreOrder(Root);
	cout << "\nОбратный обход:" << endl;
	PostOrder(Root);
	cout << "\nСимметричный обход (ЛКП):" << endl;
	InOrderUp(Root);
	cout << "\nСимметричный обход (ПКЛ):" << endl;
	InOrderDown(Root);

	SearchMax(Root);// doesn't work

	DeleteKey(Root, 9);//doesn't work
	//Root = DeleteNode(Root, 1);
	Print(Root);

	DeleteAll(Root);

	cin.get();
	return 0;
}