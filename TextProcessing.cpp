#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <vector>
using namespace std;

bool get_filelist_from_dir(std::string path, std::vector<std::string>& files)
{
	intptr_t   hFile = 0;//intptr_t��uintptr_t��ʲô����:typedef long int/ typedef unsigned long int
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//assign�����������Ϊ�Ƚ�ԭ�ַ�����գ�Ȼ�����µ�ֵ���滻��
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//�Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					get_filelist_from_dir(p.assign(path).append("\\").append(fileinfo.name), files);//���ļ����µݹ����
			}
			else//���ļ���
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int main()
{
	std::string original_file_path = "E:\\project\\VisualStudio\\DelLine\\20191218\\";
	std::string command = "mkdir -p " + original_file_path + "data\\";
	system(command.c_str());

	std::vector<std::string> file_list;
	if (!get_filelist_from_dir(original_file_path, file_list))
	{
		std::cout << "open file error!" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "��⵽ԭʼ���ݹ�" << file_list.size() <<"���ļ���"<< std::endl;
	}

	char lineData[1024] = { 0 };
	std::string lineDataStr;
	std::string GTStr;

	std::string::size_type idx;
	std::ifstream in;
	std::ofstream out;

	for (int i = 0; i < file_list.size(); i++)
	{

		std::string originalfile = original_file_path + file_list[i];

		std::string Outfile = original_file_path + "data\\" + file_list[i];

		in.open(originalfile);
		out.open(Outfile, ios::trunc);

		int lineNum = 0;
		while (in.getline(lineData, 1024))
		{
			lineDataStr = lineData;
			//std::cout << lineData << std::endl;
			idx = lineDataStr.find("info=");
			if (idx != string::npos)
			{
				GTStr = lineDataStr.substr(idx + 5);
				out << GTStr << "\n";
				lineNum++;
			}

			std::cout << "�ѽ� " << GTStr << " д������ļ�" << std::endl;


		}
		std::cout << file_list[i] << "�й�����" << lineNum << "�����ݡ�" << std::endl;
		in.close();
		out.close();
	}


}