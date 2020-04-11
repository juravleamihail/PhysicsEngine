#include "stdafx.h"
#include "Model.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Model::Model()
{
}

Model::~Model()
{
}

Vector3 ReadVector3String(string vector3)
{
	stringstream iss(vector3);
	string firstElement, secondElement, thirdElement;
	getline(iss, firstElement, ',');
	getline(iss, secondElement, ',');
	getline(iss, thirdElement);
	return Vector3(stof(firstElement), stof(secondElement), stof(thirdElement));
}

Vector2 ReadVector2String(string vector2)
{
	stringstream iss(vector2);
	string firstElement, secondElement;
	getline(iss, firstElement, ',');
	getline(iss, secondElement, ',');
	return Vector2(stof(firstElement), stof(secondElement));
}

void Model::ReadIndicesString(std::string indicesString)
{
	stringstream iss(indicesString);
	string firstElement, secondElement, thirdElement;
	getline(iss, firstElement, ',');
	getline(iss, secondElement, ',');
	getline(iss, thirdElement);
	mr->indicesVector.push_back(stoi(firstElement));
	mr->indicesVector.push_back(stoi(secondElement));
	mr->indicesVector.push_back(stoi(thirdElement));
}

int isSubstring(string s1, string s2)
{
	int M = s1.length();
	int N = s2.length();

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) {
		int j;

		/* For current index i, check for pattern match */
		for (j = 0; j < M; j++)
			if (s2[i + j] != s1[j])
				break;

		if (j == M)
			return i;
	}

	return -1;
}

void Model::Load()
{
	string line;
	string name;
	ifstream myfile(mr->path);
	bool isAtIndicesText = false;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			stringstream iss(line);
			string emptyString, positionString, normString, binormString, tgtString, uvString;
			if (!isAtIndicesText)
			{
				Vertex modelVertex;
				getline(iss, emptyString, '[');
				getline(iss, positionString, ']');
				if (positionString != "")
				{
					modelVertex.pos = ReadVector3String(positionString);
					getline(iss, emptyString, '[');
					getline(iss, normString, ']');
					modelVertex.norm = ReadVector3String(normString);
					getline(iss, emptyString, '[');
					getline(iss, binormString, ']');
					modelVertex.binorm = ReadVector3String(binormString);
					getline(iss, emptyString, '[');
					getline(iss, tgtString, ']');
					modelVertex.tgt = ReadVector3String(tgtString);
					getline(iss, emptyString, '[');
					getline(iss, uvString, ']');
					modelVertex.uv = ReadVector2String(uvString);
					mr->modelVerticesVector.push_back(modelVertex);
				}

				int res = isSubstring("NrIndices", line);
				if (res != -1)
					isAtIndicesText = true;
			}
			else
			{
				string index;
				getline(iss, emptyString, '.');
				getline(iss, index);
				if (index != "")
				{
					ReadIndicesString(index);
					int bbb = 3;
				}
			}
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}
