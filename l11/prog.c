int main(int argc, char ** argv)
{
 int * array = new int[100];
 array[1004] = 12;
 return array[1004];
}
