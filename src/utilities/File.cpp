/*

void	copy( string fromStr, FILE* to )
{
	FILE * from;
	size_t	lSize;
	char* buffer = 0;
	size_t	result;

	from = fopen ( fromStr.c_str() , "r" );
	if (!from) throw Except("File error");


	// obtain file size:
	fseek (from , 0 , SEEK_END);
	lSize = ftell (from);
	rewind (from);


	// allocate memory to contain the whole file:
	buffer = new char[sizeof(char)*lSize];
	if (!buffer) throw Except("Memory error");


	// copy the file into the buffer:
	result = fread (buffer,1,lSize,from);
	if (result != lSize) throw Except("Reading error");

	


	// the whole file is now loaded in the memory buffer.

	// close input file
	fclose (from);

	// append buffer to output file
	fwrite (buffer , 1, lSize, to);





	// terminate
	delete[] buffer;
}
*/
