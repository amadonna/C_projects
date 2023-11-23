#include "backend.h"

int readOne(char *fileName, data_struct *myData) {
  int ret = 0;
  FILE *fp = fopen(fileName, "r");
  char str[255];
  char *estr = NULL;
  int stopFlag = 0;
  if (fp != NULL) {
    while (!stopFlag) {
      estr = fgets(str, sizeof(str), fp);
      if (estr != NULL) {
        if (str[0] == 'v' && str[1] == ' ') myData->countVertex += 3;
        if (str[0] == 'f' && str[1] == ' ') {
          myData->countEdges++;
          myData->countFacets += getCountMemory(str);
        }
      } else {
        stopFlag = 1;
      }
    }
    fclose(fp);
  } else {
    ret = -1;
  }
  if (estr) {
    free(estr);
  }
  return ret;
}

void readTwo(char *fileName, data_struct *myData) {
  int stopFlag = 0;

  myData->vector_3d = calloc(myData->countVertex, sizeof(double));
  if (myData->vector_3d == NULL) stopFlag = 1;

  myData->poligons = calloc(myData->countFacets, sizeof(unsigned int));
  if (myData->poligons == NULL) stopFlag = 1;

  if (!stopFlag) {
    double x = 0, y = 0, z = 0;
    char ch = ' ';
    char str[255] = "\0";
    char *estr;
    int i = 0, index = 0;
    FILE *fp = fopen(fileName, "r");
    if (fp != NULL) {
      while (!stopFlag) {
        estr = fgets(str, sizeof(str), fp);
        if (estr != NULL) {
          if (str[0] == 'v' && str[1] == ' ') {
            sscanf(str, "%c %lf %lf %lf", &ch, &x, &y, &z);
            myData->vector_3d[i] = x;
            myData->vector_3d[i + 1] = y;
            myData->vector_3d[i + 2] = z;
            i += 3;
          }
          if (str[0] == 'f' && str[1] == ' ') {
            getDigit(str, myData, &index);
          }
        } else
          stopFlag = 1;
      }
      if (estr) {
        free(estr);
      }
      fclose(fp);
    } else {
      free(myData->vector_3d);
      free(myData->poligons);
    }
  }
}

int getCountMemory(char *str) {
  int rez = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] >= 48 && str[i] <= 57 && str[i - 1] == ' ') rez++;
  }
  return rez * 2;
}

void getDigit(char *str, data_struct *myData, int *index) {
  int countNum = 0, firstElem = 0;
  char digit[255] = "";

  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] >= 48 && str[i] <= 57 && str[i - 1] == ' ') {
      int stopFlag = 0;
      int k = 0;
      while (!stopFlag) {
        digit[k] = str[i];
        k++;
        i++;
        if ((str[i] < 48 || str[i] > 57)) {
          stopFlag = 1;
          countNum++;
        }
      }
      if (strlen(digit) > 0) {
        if (countNum == 1) {
          myData->poligons[*index] = atoi(digit) - 1;
          firstElem = myData->poligons[*index];
          *index += 1;
        }
        if (countNum != 1) {
          myData->poligons[*index] = atoi(digit) - 1;
          myData->poligons[*index + 1] = atoi(digit) - 1;
          *index += 2;
        }
        memset(digit, '\0', strlen(digit));
      }
    }
  }
  myData->poligons[*index] = firstElem;
  *index += 1;
}

void centerVertex(data_struct *myData) {
  unsigned int i = 0;

  double *ver_x = NULL;
  double *ver_y = NULL;
  double *ver_z = NULL;
  double center_x = 0;
  double center_y = 0;
  double center_z = 0;

  ver_x = calloc(myData->countVertex / 3, sizeof(double));
  ver_y = calloc(myData->countVertex / 3, sizeof(double));
  ver_z = calloc(myData->countVertex / 3, sizeof(double));

  if (ver_x != NULL && ver_y != NULL && ver_z != NULL) {
    unsigned int j = 0;

    while (i < myData->countVertex) {
      ver_x[j] = myData->vector_3d[i];
      i++;
      ver_y[j] = myData->vector_3d[i];
      i++;
      ver_z[j] = myData->vector_3d[i];
      i++;
      j++;
    }

    center_x = findMin(ver_x, myData->countVertex / 3) +
               (findMax(ver_x, myData->countVertex / 3) -
                findMin(ver_x, myData->countVertex / 3)) /
                   2;
    center_y = findMin(ver_y, myData->countVertex / 3) +
               (findMax(ver_y, myData->countVertex / 3) -
                findMin(ver_y, myData->countVertex / 3)) /
                   2;
    center_z = findMin(ver_z, myData->countVertex / 3) +
               (findMax(ver_z, myData->countVertex / 3) -
                findMin(ver_z, myData->countVertex / 3)) /
                   2;

    unsigned int k = 0;
    while (k < myData->countVertex) {
      myData->vector_3d[k] -= center_x;
      k++;
      myData->vector_3d[k] -= center_y;
      k++;
      myData->vector_3d[k] -= center_z;
      k++;
    }
    free(ver_x);
    free(ver_y);
    free(ver_z);
  }
}

double findMax(double *mas_d, int c) {
  int i = 0;
  double begin = mas_d[0];
  while (i < c) {
    if (mas_d[i] > begin) begin = mas_d[i];
    i++;
  }
  return begin;
}

double findMin(double *mas_d, int c) {
  int i = 0;
  double begin = mas_d[0];
  while (i < c) {
    if (mas_d[i] < begin) begin = mas_d[i];
    i++;
  }
  return begin;
}

void changeScale(data_struct *myData, double value) {
  unsigned int i = 0;

  double *ver_x = NULL;
  double *ver_y = NULL;
  double *ver_z = NULL;

  ver_x = calloc(myData->countVertex / 3, sizeof(double));
  ver_y = calloc(myData->countVertex / 3, sizeof(double));
  ver_z = calloc(myData->countVertex / 3, sizeof(double));
  if (ver_x != NULL && ver_y != NULL && ver_z != NULL) {
    unsigned int j = 0;
    double d_max = 0;
    double scale = 0;
    while (i < myData->countVertex) {
      ver_x[j] = myData->vector_3d[i];
      i++;
      ver_y[j] = myData->vector_3d[i];
      i++;
      ver_z[j] = myData->vector_3d[i];
      i++;
      j++;
    }
    d_max = findMax(myData->vector_3d, myData->countVertex);
    if (d_max != 0) scale = (value - value * -1) / d_max;
    unsigned int k = 0;
    while (k < myData->countVertex) {
      myData->vector_3d[k] *= scale;
      k++;
      myData->vector_3d[k] *= scale;
      k++;
      myData->vector_3d[k] *= scale;
      k++;
    }
    free(ver_x);
    free(ver_y);
    free(ver_z);
  }
}

void cleanAll(data_struct *myData) {
  if (myData->vector_3d != NULL) {
    free(myData->vector_3d);
    myData->vector_3d = NULL;
  }
  if (myData->poligons != NULL) {
    free(myData->poligons);
    myData->poligons = NULL;
  }
}

void rote_X(data_struct *myData, double angle) {
  int i = 0;
  if (myData != NULL) {
    while (i < (int)myData->countVertex) {
      double temp_y = myData->vector_3d[i + 1];
      double temp_z = myData->vector_3d[i + 2];
      myData->vector_3d[i + 1] = cos(angle) * temp_y - sin(angle) * temp_z;
      myData->vector_3d[i + 2] = sin(angle) * temp_y + cos(angle) * temp_z;
      i += 3;
    }
  }
}
void rote_Y(data_struct *myData, double angle) {
  int i = 0;
  if (myData != NULL) {
    while (i < (int)myData->countVertex) {
      double temp_x = myData->vector_3d[i];
      double temp_z = myData->vector_3d[i + 2];
      myData->vector_3d[i] = cos(angle) * temp_x - sin(angle) * temp_z;
      myData->vector_3d[i + 2] = sin(angle) * temp_x + cos(angle) * temp_z;
      i += 3;
    }
  }
}

void rote_Z(data_struct *myData, double angle) {
  int i = 0;
  if (myData != NULL) {
    while (i < (int)myData->countVertex) {
      double temp_x = myData->vector_3d[i];
      double temp_y = myData->vector_3d[i + 1];
      myData->vector_3d[i] = cos(angle) * temp_x - sin(angle) * temp_y;
      myData->vector_3d[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
      i += 3;
    }
  }
}
