#include "read.h"

#define INPUT_FILE_NAME "../pnt/recipe 1.pnt"

int main()
{   
    string filename = INPUT_FILE_NAME;
    int rows, cols;
    
    ReadFileInfo::getInstance().Getsize(&rows, &cols, filename);
    std::cout << "Rows: " << rows << ", Cols: " << cols << std::endl;

    vector<vector<int>> pre(rows,vector<int>(cols, 0)); 
    vector<vector<int>> post(rows,vector<int>(cols, 0));
    vector<int> M(rows, 0);
    //vector<int> M;

    ReadFileInfo::getInstance().LY_pnt2NW(filename, pre, post, M);

    cout << "M0: " << endl;
    for(int token : M){
        cout << token << " ";
    }
    cout << endl;

    cout << "Pre: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << pre[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Post: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << post[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}