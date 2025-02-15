#include "common.hpp"

class Fc
{
    private:
        
    public:
        int input_size;
        int output_size;
        Mat2D weight;
        Mat1D bias;
        Fc(int input_size, int output_size);
        //~Fc();
        Mat1D forward(Mat1D in_mat, int activation);
        void init_weight();
        void weight_load(char* path);
		void bias_load(char* path);

};

Fc::Fc(int in_size, int out_size){
    this->input_size = in_size;
    this->output_size = out_size;
    init_weight();
}

Mat1D Fc::forward(Mat1D in_mat,int activation){
    Mat1D out;
    for(int i=0; i<this->weight.size(); i++){
        float sum=0;
        for(int j=0; j<in_mat.size(); j++){
            sum += in_mat[j]*this->weight[i][j];
        }
        sum += bias[i];
		if(activation == RELU){
			if(sum<0){
				sum=0;
			}
		}
        out.push_back(sum);
    }
    return out;
}

void Fc::init_weight(){
	int output_size= this->output_size;
    int input_size = this->input_size;

    weight.resize(output_size);
    bias.resize(input_size);

    cv::Mat A(output_size,input_size, CV_32F);
	for(int i=0; i<output_size; i++){
        weight[i].resize(input_size);
        bias[i] = ((float)(rand() / (float(RAND_MAX))) -0.5);
		for(int j=0; j<input_size; j++){
			weight[i][j]=((float)(rand() / (float(RAND_MAX))) -0.5);
		}
	}
}	


void Fc::weight_load(char* path){
	FILE* fp = fopen(path,"r");
	double val;
	for(int i=0; i<this->output_size; i++){
		for(int j=0; j<this->input_size; j++){
			fscanf(fp,"%lf\n",&val);
			this->weight[i][j] = (float)val;
		}
	}
	fclose(fp);
}

void Fc::bias_load(char* path){
	FILE* fp = fopen(path,"r");
	double val;
	for(int i=0; i<this->output_size; i++){
		fscanf(fp,"%lf\n",&val);
		this->bias[i] =(float)val;
	}
	fclose(fp);
}
