bool isdigit_switch(char c) {
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    }
    return false;
}

bool isdigit_if(char c) {
    return (c >= '0' && c <= '9');
}