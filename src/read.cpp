#include "read.h"

ReadFileInfo& ReadFileInfo::getInstance(){
    static ReadFileInfo instance;
    return instance;
}

void ReadFileInfo::Getsize(int *rows, int *cols, string fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    int m = 0, n = 0;
    std::string line0, line;

    std::getline(file, line0); // Read the first line

    while (std::getline(file, line))
    {
        if (line[0] == '@') {
            break;
        }

        std::stringstream ss(line);
        std::string token;

        // 在读取每一行时候，跳过P M,读取PRE和POST
        ss >> token;
        //cout << "1: " << token << endl;

        ss >> token;
        //cout << "2: " << token << endl;

        while (ss >> token)
        {
            if (std::atoi(token.c_str()) > n)
                n = std::atoi(token.c_str());
            if (token.find(':') != std::string::npos)
            {
                ss >> token; // Skip next token after ':'
            }
        }
        m++;
    }

    file.close();
    *rows = m;
    *cols = n;
    PetriNet::getInstance().nums_place = m;
    PetriNet::getInstance().nums_transition = n;
}

void ReadFileInfo::LY_pnt2NW(string fileName, vector<vector<int>> &input, vector<vector<int>> &output, vector<int> &M)
{
    ifstream fid(fileName);
    if (!fid.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        exit(1);
    }

    string line0, line;
    getline(fid, line0); // Skip the first line

    int k = 0;
    while (getline(fid, line))
    {
        if (line[0] == '@')
            break;

        stringstream ss(line);
        string token;
        //跳过P
        ss >> token;
        //读取到初始标记
        ss >> token;
        M[k] = stoi(token);

        //读取pre
        string preStr;
        getline(ss, preStr, ',');
        //cout << "prestr: " << preStr << "  size: " << preStr.size() << endl;
        istringstream iss(preStr);
        while(getline(iss, token, ' ')){
            if(token == " " || token.size() == 0) continue;
            input[k][stoi(token) - 1] = 1;
            //cout << "pre:" << token << endl;
        } 

        string token2;
        while(ss >> token2){
            //cout << token2 << " ";
            output[k][stoi(token2) - 1] = 1;
        }
        //cout << endl;
       
        k++;
    }

    fid.close();
}

bool ReadFileInfo::initPetriNet(string filename){
    int rows, cols;
    
    ReadFileInfo::getInstance().Getsize(&rows, &cols, filename);
    //std::cout << "Rows: " << rows << ", Cols: " << cols << std::endl;

    vector<vector<int>> pre(rows,vector<int>(cols, 0)); 
    vector<vector<int>> post(rows,vector<int>(cols, 0));
    vector<int> M(rows, 0);

    ReadFileInfo::getInstance().LY_pnt2NW(filename, pre, post, M);

    PetriNet::getInstance().pre_incidence = post;
    PetriNet::getInstance().post_incidence = pre;
    PetriNet::getInstance().M0_vector = M;

    Eigen::MatrixXi preMatrix(rows, cols);
    Eigen::MatrixXi postMatrix(rows, cols);
    Eigen::VectorXi M0matrix(rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            preMatrix(i, j) = post[i][j];
            postMatrix(i, j) = pre[i][j];
        }
        M0matrix(i) = M[i];
    }

    PetriNet::getInstance().pre_matrix = preMatrix;
    PetriNet::getInstance().post_matrix = postMatrix;
    PetriNet::getInstance().M0_matrix = M0matrix;

    vector<vector<int>> incidence_v(rows,vector<int>(cols, 0));
    Eigen::MatrixXi incidence_m(rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            incidence_v[i][j] = postMatrix(i, j) - preMatrix(i, j);
            incidence_m(i, j) = incidence_v[i][j];
        }
    }

    PetriNet::getInstance().incidence_vector = incidence_v;
    PetriNet::getInstance().incidence_matrix = incidence_m;
}
