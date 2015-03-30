#include <vector>
#include <iostream>
using namespace std;
int main ( int argc, char *argv[] )
<%

    vector<int> vecint;
    for (int i = 0; i < 10; ++ i)
    <%
        vecint.push_back(i);
    %>
    cout << vecint<:4:> << endl;
    int(y) = 3;

    return 0;
%>			/* ----------  end of function main  ---------- */

