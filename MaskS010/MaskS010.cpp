#include <iostream> // программа, которая ищет в строке все вхождения задаваемой маски и заменяет на заданную строку замены. Выдает список номеров символов, начиная с которого была сделана замена или -1 если замен не было.

void FindMaskRec(bool wasstar, int i, int j, bool nword);
void FindMask(int i);
void masksize();
int inpsize(int i);
void end();
void Replace();

int ms;
int rp = 0;
int result[100];

char input[255], mask[255];
char replace[255];
char newinp[255];


int main()
{
	std::cout << "String: ";
	std::cin.getline(input, 255);
	std::cout << "Mask: ";
	std::cin.getline(mask, 255);
	std::cout << "Replace to: ";
	std::cin.getline(replace, 255);
	masksize();
	FindMask(0);
	Replace();
	std::cout << "Result: " << newinp;
}

void Replace()
{
	if (rp != 0)
	{
		int i = 0, j = 0, k = 0, n = 0;
		while (input[i] != '\0')
		{
			if (i == result[n])
			{
				k = 0;
				n++;
				int inps = inpsize(i);
				i += inps - 1;
				while (replace[k] != '\0')
				{
					newinp[j] = replace[k];
					k++;
					j++;
				}
				j--;
			}
			else
				newinp[j] = input[i];
			i++;
			j++;
		}
		newinp[j] = '\0';
	}
	else
	{
		int i = 0;
		while (input[i] != '\0')
		{
			newinp[i] = input[i];
			i++;
		}
		newinp[i] = '\0';
	}
}


void FindMaskRec(bool wasstar, int i, int j, bool nword)
{
	if (input[i] == '\0' || input[i] == ' ')
	{
		bool ended = false;
		while (mask[j] != '\0')
		{
			if (mask[j] != '*')
			{
				if (!nword) rp--;
				if (input[i] == ' ') FindMask(i + 1);
				else end();
				ended = true;
				break;
			}
			j++;
		}
		if (!ended)
		{
			if (input[i] == ' ') FindMask(i + 1);
			else end();
		}
	}
	else if (mask[j] == '\0')
	{
		if (mask[j - 1] == '*')
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') FindMask(i + 1);
			else end();
		}
		else
		{
			if (!nword) rp--;
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') FindMask(i + 1);
			else end();
		}
	}
	else if (mask[j] == '*')
	{
		if (nword) result[rp++] = i;
		FindMaskRec(true, i, j + 1, false);
	}
	else if (mask[j] == '?')
	{
		if (wasstar)
		{
			if (mask[j + 1] == '\0')
			{
				while (input[i] != ' ' && input[i] != '\0') i++;
				if (input[i] == ' ') FindMask(i + 1);
				else end();
			}
			else return FindMaskRec(true, i + 1, j + 1, nword);
		}
		else
		{
			if (nword) result[rp++] = i;
			FindMaskRec(false, i + 1, j + 1, false);
		}
	}
	else if (mask[j] == input[i])
	{
		if (nword) result[rp++] = i;
		FindMaskRec(false, i + 1, j + 1, false);
	}
	else if (wasstar) return FindMaskRec(true, i + 1, j, nword);
	else
	{
		bool found = false;
		while (j >= 0)
		{
			if (mask[j] == '*')
			{
				found = true;
				break;
			}
			j--;
		}
		if (found) return FindMaskRec(true, i + 1, j + 1, nword);
		else
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') FindMask(i + 1);
			else end();
		}
	}
}

void FindMask(int i)
{
	int inps = inpsize(i);
	if (ms > inps)
	{
		if (input[i + inps] == ' ')
		{
			i += inps;
			FindMask(i);
		}
		else end();
	}
	else FindMaskRec(false, i, 0, true);
}

void masksize()
{
	int i = 0;
	ms = 0;
	while (mask[i] != '\0')
	{
		if (mask[i] != '*')
			ms++;
		i++;
	}
}

int inpsize(int i)
{
	int size = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		i++;
		size++;
	}
	return size;
}

void end()
{
	if (rp == 0)
	{
		result[0] = -1;
		rp++;
	}
}
