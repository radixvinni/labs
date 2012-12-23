#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <time.h>
#include <fstream>


void set_low_keys (unsigned long	*key);
void key_found (unsigned long	slice, unsigned long	*keybits);
void build_samples (unsigned long	*p, unsigned long	*c, unsigned long	*k, int		practice_flag);
void increment_key (unsigned long	*key);
unsigned long InitialData1[20] = {37,50,54,50,56,0,43,43,74,71,32,36,16,43,56,100,50,25,15,17};
unsigned long InitialData2[20] = {35,51,54,58,55,32,36,69,27,39,35,40,16,44,55,14,58,75,18,15};

char* oclLoadProgSource(const char* cFilename, const char* cPreamble, size_t* szFinalLength)
{
    // locals 
    FILE* pFileStream = NULL;
    size_t szSourceLength;

    // open the OpenCL source code file
        pFileStream = fopen(cFilename, "rb");
        if(pFileStream == 0) 
        {       
            return NULL;
        }
    
    size_t szPreambleLength = strlen(cPreamble);

    // get the length of the source code
    fseek(pFileStream, 0, SEEK_END); 
    szSourceLength = ftell(pFileStream);
    fseek(pFileStream, 0, SEEK_SET); 

    // allocate a buffer for the source code string and read it in
    char* cSourceString = (char *)malloc(szSourceLength + szPreambleLength + 1); 
    memcpy(cSourceString, cPreamble, szPreambleLength);
    if (fread((cSourceString) + szPreambleLength, szSourceLength, 1, pFileStream) != 1)
    {
        fclose(pFileStream);
        free(cSourceString);
        return 0;
    }

    // close the file and return the total length of the combined (preamble + source) string
    fclose(pFileStream);
    if(szFinalLength != 0)
    {
        *szFinalLength = szSourceLength + szPreambleLength;
    }
    cSourceString[szSourceLength + szPreambleLength] = '\0';

    return cSourceString;
}


int main(int argc, char **argv)
{
	int	start,end;
	unsigned long	p[64], c[64], k[56];
	unsigned long	res;

	build_samples (p, c, k, 0);
	set_low_keys(k);
	
	cl_platform_id cpPlatform;
	clGetPlatformIDs(1, &cpPlatform, NULL);

	cl_device_id cdDevice;
	clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &cdDevice, NULL);

	char cBuffer[1024];
	clGetDeviceInfo(cdDevice, CL_DEVICE_NAME, sizeof(cBuffer), &cBuffer, NULL);
	printf("CL_DEVICE_NAME:\t\t%s\n", cBuffer);
	clGetDeviceInfo(cdDevice, CL_DRIVER_VERSION, sizeof(cBuffer), &cBuffer, NULL);
	printf("CL_DRIVER_VERSION:\t%s\n\n", cBuffer);
	cl_uint compute_units;
    clGetDeviceInfo(cdDevice, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(compute_units), &compute_units, NULL);
    printf("CL_DEVICE_MAX_COMPUTE_UNITS:\t%u\n", compute_units);
	size_t workitem_dims;
    clGetDeviceInfo(cdDevice, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(workitem_dims), &workitem_dims, NULL);
    printf("CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:\t%u\n", workitem_dims);
	size_t workitem_size[3];
    clGetDeviceInfo(cdDevice, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(workitem_size), &workitem_size, NULL);
    printf("CL_DEVICE_MAX_WORK_ITEM_SIZES:\t%u / %u / %u \n", workitem_size[0], workitem_size[1], workitem_size[2]);
    size_t workgroup_size;
    clGetDeviceInfo(cdDevice, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(workgroup_size), &workgroup_size, NULL);
    printf("CL_DEVICE_MAX_WORK_GROUP_SIZE:\t%u\n", workgroup_size);
	cl_uint clock_frequency;
    clGetDeviceInfo(cdDevice, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clock_frequency), &clock_frequency, NULL);
    printf("CL_DEVICE_MAX_CLOCK_FREQUENCY:\t%u MHz\n", clock_frequency);

	cl_context GPUContext = clCreateContext(0, 1, &cdDevice, NULL, NULL, NULL);
  
	cl_command_queue cqCommandQueue = clCreateCommandQueue(GPUContext, cdDevice, 0, NULL);
  
	cl_mem GPUVector1 = clCreateBuffer(GPUContext, CL_MEM_READ_ONLY |
									CL_MEM_USE_HOST_PTR, sizeof(unsigned long) * 64, p, NULL);
	cl_mem GPUVector2 = clCreateBuffer(GPUContext, CL_MEM_READ_ONLY |
									CL_MEM_USE_HOST_PTR, sizeof(unsigned long) * 64, c, NULL);
	cl_mem GPUVector3 = clCreateBuffer(GPUContext, CL_MEM_READ_ONLY |
									CL_MEM_USE_HOST_PTR, sizeof(unsigned long) * 56, k, NULL);
  
	cl_mem GPUOutputVector = clCreateBuffer(GPUContext, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,
									sizeof(unsigned long), &res, NULL);

	size_t szKernelLength;
	char* cSourceCL = oclLoadProgSource("ocl_deseval.cl", "", &szKernelLength);
	cl_program OpenCLProgram = clCreateProgramWithSource(GPUContext, 1,
									(const char **)&cSourceCL, &szKernelLength, NULL);

	if (clBuildProgram(OpenCLProgram, 0, NULL, NULL, NULL, NULL)!=CL_SUCCESS)
	{ 
		char cBuffer[2048];
		if(clGetProgramBuildInfo(OpenCLProgram,cdDevice,CL_PROGRAM_BUILD_LOG,sizeof(cBuffer),cBuffer,NULL)==CL_SUCCESS);
		printf("Build error:\n%s\n",cBuffer);exit(1); 
	}
	cl_kernel OpenCLVectorAdd = clCreateKernel(OpenCLProgram, "keysearch", NULL);

	clSetKernelArg(OpenCLVectorAdd, 0, sizeof(cl_mem), (void*)&GPUOutputVector);
	clSetKernelArg(OpenCLVectorAdd, 1, sizeof(cl_mem), (void*)&GPUVector1);
	clSetKernelArg(OpenCLVectorAdd, 2, sizeof(cl_mem), (void*)&GPUVector2);
	clSetKernelArg(OpenCLVectorAdd, 3, sizeof(cl_mem), (void*)&GPUVector3);

	size_t WorkSize[1] = {1024};
	start=clock();
	for (int i=0; i<1024; i++) {
		//clEnqueueWriteBuffer(cqCommandQueue, GPUOutputVector, CL_TRUE, 0,
		//									56 * sizeof(unsigned long), k, 0, NULL, NULL);
		clEnqueueNDRangeKernel(cqCommandQueue, OpenCLVectorAdd, 1, NULL,
														WorkSize, NULL, 0, NULL, NULL);
		//clEnqueueReadBuffer(cqCommandQueue, GPUOutputVector, CL_TRUE, 0,
		//									sizeof(unsigned long), &res, 0, NULL, NULL);
		if(res!=0){
			printf("Key found\n");
			//key_found(res,k);
			break;
		}
		increment_key (k);
	}
	end=clock();

	clReleaseKernel(OpenCLVectorAdd);
	clReleaseProgram(OpenCLProgram);
	clReleaseCommandQueue(cqCommandQueue);
	clReleaseContext(GPUContext);
	clReleaseMemObject(GPUVector1);
	clReleaseMemObject(GPUVector2);
	clReleaseMemObject(GPUOutputVector);
	
	printf ("Searched %i keys in %.3f seconds\n", 1000000, ((double)(end-start))/CLOCKS_PER_SEC);
	return 0;
}
