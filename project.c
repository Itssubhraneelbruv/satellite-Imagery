#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include<stdlib.h>
#include<string.h>

int APOD(void);
int MRP(void);
int EARTH(void);
int main()
{
    int c;
    printf("\n\nSelect the number placed in front ofyour prefferable option\n");
    printf("(1)APOD-Astronomy Picture of the Day\n(2)Earth-Unlock the significant public investment in earth observation data(CAUTION:THIS SATTELITE HAS A FEW LATITUDE AND LONGITUDE MISSING)\n(3)Mars Rover Photos-Image data gatheres by NASA's Curiosity, Opportunity, and spirit rovers on Mars");
    printf("\nyour choice: ");
    scanf("%d",&c);
    switch(c){
       case 1: APOD();
		break;
       case 2: EARTH();
        break;
       case 3: MRP();
		break;
       default: printf("\nWrong selection!!! Try again!!!");
    }
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  
  return realsize;
}

int APOD(void) {
  CURL *curl;
  CURLcode res;
  int day, month, year;
  char link[200];
  struct MemoryStruct mem;
  mem.memory = malloc(1);
  mem.size = 0;

  printf("Enter the day: ");
  scanf("%d", &day);
  printf("Enter the month: ");
  scanf("%d", &month);
  printf("Enter the year: ");
  scanf("%d", &year);

  sprintf(link, "https://api.nasa.gov/planetary/apod?api_key=jFG4H5Gl9LGmpHgkJ1Nw99AjhkIL8KRNkWfL9pwK&date=%04d-%02d-%02d", year, month, day);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, link);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&mem);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
cJSON *json = cJSON_Parse(mem.memory);

cJSON *copyright = cJSON_GetObjectItem(json, "copyright");
const char *copyright_str = cJSON_GetStringValue(copyright);

cJSON *explanation = cJSON_GetObjectItem(json, "explanation");
const char *explanation_str = cJSON_GetStringValue(explanation);

cJSON *media_type = cJSON_GetObjectItem(json, "media_type");
const char *media_type_str = cJSON_GetStringValue(media_type);

cJSON *url = cJSON_GetObjectItem(json, "url");
const char *url_str = cJSON_GetStringValue(url);

if(url_str == NULL && media_type_str == NULL && explanation_str == NULL && copyright_str == NULL){
    printf("no pictures for this date");
}else {
    printf("Copyright: %s\n", copyright_str);
    printf("Explanation: %s\n", explanation_str);
    printf("Media Type: %s\n", media_type_str);
    printf("URL: %s\n", url_str);
}

cJSON_Delete(json);
free(mem.memory);
  return 0;
}

int EARTH(void) {
  CURL *curl;
  CURLcode res;
  int day, month, year;
  struct MemoryStruct mem;
  double lat;
  double lon;
  char link[200];

  printf("Enter the day: ");
  scanf("%d", &day);
  printf("Enter the month: ");
  scanf("%d", &month);
  printf("Enter the year: ");
  scanf("%d", &year);
  printf("Enter the longitude: ");
  scanf("%lf", &lon);
  printf("Enter the latitude: ");
  scanf("%lf", &lat);

  mem.memory = malloc(1);
  mem.size = 0;


  sprintf(link, "https://api.nasa.gov/planetary/earth/assets?lon=%lf&lat=%lf&date=%04d-%02d-%02d&dim=0.15&api_key=jFG4H5Gl9LGmpHgkJ1Nw99AjhkIL8KRNkWfL9pwK", lon, lat, year, month, day);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, link);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&mem);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
cJSON *json = cJSON_Parse(mem.memory);

cJSON *url = cJSON_GetObjectItem(json, "url");
const char *url_str = cJSON_GetStringValue(url);
if(url_str == NULL){
    printf("no pictures for this latitude and longitude or date");
}else {
    printf("URL: %s\n", url_str);
}


cJSON_Delete(json);
free(mem.memory);
  return 0;
}

int MRP(void) {
  CURL *curl;
  CURLcode res;
  int day, month, year;
  char url[200];
  struct MemoryStruct mem;
  mem.memory = malloc(1);
  mem.size = 0;

  printf("Enter the day: ");
  scanf("%d", &day);
  printf("Enter the month: ");
  scanf("%d", &month);
  printf("Enter the year: ");
  scanf("%d", &year);

  sprintf(url, "https://api.nasa.gov/mars-photos/api/v1/rovers/curiosity/photos?earth_date=%04d-%02d-%02d&api_key=jFG4H5Gl9LGmpHgkJ1Nw99AjhkIL8KRNkWfL9pwK", year, month, day);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&mem);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
cJSON *json = cJSON_Parse(mem.memory);
cJSON *photos = cJSON_GetObjectItem(json, "photos");
cJSON *photo = cJSON_GetArrayItem(photos, 0);
cJSON *img_src = cJSON_GetObjectItem(photo, "img_src");
const char *img_src_str = cJSON_GetStringValue(img_src);
if (img_src_str == NULL) {
    printf("No pictures found for this date");
} else {
    printf("img_src_str: %s\n", img_src_str);

}
cJSON_Delete(json);
free(mem.memory);
  return 0;
}