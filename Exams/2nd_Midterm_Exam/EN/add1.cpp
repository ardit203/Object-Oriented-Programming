#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;

class WrongLabelsFormatException{
public:
    void message(){
        cout << "Labels must have the same length"<<endl;
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Evaluator{
protected:
    char actual[100];
    char predicted[100];
public:
    Evaluator(char *actual= nullptr, char *predicted= nullptr){
        if(strlen(actual)!= strlen(predicted)){
            throw WrongLabelsFormatException();
        }
        strcpy(this->actual,actual);
        strcpy(this->predicted,predicted);
    }
    virtual double evaluate()=0;
    virtual void print()=0;
    bool operator>=(Evaluator &v){
        return evaluate()>=v.evaluate();
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////

class AccuracyEvaluator:public Evaluator{
private:

public:
    AccuracyEvaluator(char *actual= nullptr, char *predicted= nullptr): Evaluator(actual,predicted){}

    double evaluate() override {
        int correctPrediction=0;
        for(int i=0 ; i< strlen(actual) ; i++){
            if(actual[i]== predicted[i]){
                correctPrediction++;
            }
        }
        return double(correctPrediction)/ strlen(actual);
    }

    void print() override {
        cout<<"Number of data points: "<<strlen(actual);
        cout<<" Prediction Accuracy: "<<evaluate()<<endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////

class SensitivityEvaluator:public Evaluator{
protected:

public:
    SensitivityEvaluator(char *actual= nullptr, char *predicted= nullptr): Evaluator(actual,predicted){}

    double evaluate() override {
        int correctPrediction=0;
        int correct=0;
        for(int i=0 ; i< strlen(actual) ; i++){
            if(actual[i]=='+' && predicted[i]=='+'){
                correctPrediction++;
            }
            if(actual[i]=='+'){
                correct++;
            }
        }
        return double (correctPrediction)/correct;
    }

    void print() override {
        cout<<"Number of data points: "<<strlen(actual);
        cout<<" Prediction Sensitivity: "<<evaluate()<<endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////


Evaluator *highestScore(Evaluator **evaluators, int n){
    Evaluator *max=evaluators[0];
    for(int i=1 ; i<n ; i++){
        if(evaluators[i]>=max){
            max=evaluators[i];
        }
    }
    return max;
}



int main() {
    int testCase;
    char trueLabels[100];
    char predictedLabels[100];
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try{
            Evaluator *evaluator = new AccuracyEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        }catch (WrongLabelsFormatException &e){
            e.message();
        }

    } else if (testCase == 2) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try{
            Evaluator *evaluator = new SensitivityEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        }catch (WrongLabelsFormatException &e){
            e.message();
        }


    } else if (testCase == 3) {
        cout << "TESTING CREATION OF BOTH EVALUATORS. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;
        try{
            Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
            Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
            accuracy->print();
            sensitivity->print();
        }catch (WrongLabelsFormatException &e){
            e.message();
        }

    } else if (testCase == 4) {
        cout << "TESTING OPERATOR >=" << endl;
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy1 = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity1 = new SensitivityEvaluator(trueLabels, predictedLabels);

        accuracy->print();
        cout << (((*accuracy) >= (*sensitivity)) ? ">=" : "<") << endl;
        sensitivity->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*accuracy)) ? ">=" : "<") << endl;
        accuracy->print();
        cout << endl;

        accuracy->print();
        cout << (((*accuracy) >= (*accuracy1)) ? ">=" : "<") << endl;
        accuracy1->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*sensitivity1)) ? ">=" : "<") << endl;
        sensitivity1->print();
        cout << endl;
    } else {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION. EXCEPTION CAN HAPPEN HERE!" << endl;
        int n;
        cin >> n;
        Evaluator **evaluators = new Evaluator *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            cin >> trueLabels >> predictedLabels;
            try{
                if (type == 1) { //accuracy
                    evaluators[i] = new AccuracyEvaluator(trueLabels, predictedLabels);
                } else { //sensitivity
                    evaluators[i] = new SensitivityEvaluator(trueLabels, predictedLabels);
                }
            }catch (WrongLabelsFormatException &e){
                e.message();
                --n;
                --i;
            }

        }

        cout << "PRINT ALL EVALUATORS FIRST!" << endl;
        for (int i = 0; i < n; i++) {
            evaluators[i]->print();
        }

        cout << "RESULT FROM HIGHEST SCORE METHOD" << endl;
        highestScore(evaluators, n)->print();
    }

}