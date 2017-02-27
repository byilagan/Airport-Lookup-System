#include "airports.h"
#include <string.h>
#include <math.h>

#define pi 3.14159265358979

nodePtr ptrArray[5];
int counter = 0;
int maxDist = 0;
int maxInd = 0;
nodePtr root;
int begin = 0;

double deg2rad(double num){

  return (num*pi / 180);
}

double rad2deg(double num){
  return (num*180 / pi);
}

//calculates distance for 2 points
double distance(double lat1, double lon1, double lat2, double lon2){
  double theta, dist;
  char unit = 'M';

  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1))*sin(deg2rad(lat2)) + cos(deg2rad(lat1))*
	cos(deg2rad(lat2))*cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;

  switch(unit){
  case 'M':
	break;
  case 'K':
	dist = dist*1.609;
	break;
  case 'N':
	dist = dist*0.8684;
	break;
  }
  return dist;
}

nodePtr newNode(char* code, char* name, float lat, float lon){
  //creates a new node for airport data

  nodePtr temp = malloc(sizeof(Node));
  temp->airport.airportCode = code;
  temp->airport.airportName = name;
  temp->airport.lat = lat;
  temp->airport.lon = lon;
  temp->airport.distance = 1000000;
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}

nodePtr recursiveKDInsert(nodePtr root, nodePtr new, unsigned depth){
  if(root == NULL)
	return new;

  //used to designate whether to check x or y axis

  unsigned dimension = depth % 2;

  //traverse down tree in x or y direction according to depth
  if(dimension == 0){
	if(new->airport.lat < root->airport.lat)
	  root->left = recursiveKDInsert(root->left, new, depth+1);
	else
	  root->right = recursiveKDInsert(root->right,new,depth+1);
  }else{
	if(new->airport.lon < root->airport.lon)
	  root->left = recursiveKDInsert(root->left, new, depth+1);
	else
	  root->right = recursiveKDInsert(root->right,new,depth+1);
  }
  return root;
}

nodePtr KDInsert(nodePtr root, nodePtr new){
  return recursiveKDInsert(root,new,0);
}

void addToArray(nodePtr node){
  if(counter > 4){
	ptrArray[maxInd] = node;

	int i = 0;
	maxInd = 0;
	maxDist = 0;

	while(i < 5){
	  if(ptrArray[i]->airport.distance > maxDist){
		maxDist = ptrArray[i]->airport.distance;
		maxInd = i;
	  }
	  i++;
	}
  }else{
	ptrArray[counter] = node;
	if(node->airport.distance > maxDist){
	  maxDist = node ->airport.distance;
	  maxInd = counter;
	}
	counter++;
  }
}

nodePtr KDNearestNeighbor( nodePtr root, nodePtr nearest,
						   coordinatesA c, unsigned d){
  //empty leaf node
  if(root == NULL)
	return nearest;
  if(nearest == NULL)
	nearest = root;

  unsigned dimension = d % 2;

  //calculate distance from current node to target
  double dist = distance(root->airport.lat,root->airport.lon,
						 c.lat, c.lon);

  root->airport.distance = dist;
  //if current dist is shorter than previous closest, replace
  if(dist < maxDist || counter < 4)
	addToArray(root);

  if(root->airport.distance < nearest->airport.distance)
	nearest = root;


  //traversing down the tree either in x or y dimension depending on depth
  if(dimension == 0){
	if(c.lat < root->airport.lat && root->left)
	  nearest = KDNearestNeighbor(root->left,nearest,c,d+1);  
	else
	  nearest = KDNearestNeighbor(root->right,nearest,c,d+1);
  }else{
	if(c.lon < root->airport.lon && root->left)
	  nearest = KDNearestNeighbor(root->left,nearest,c,d+1);
	else
	  nearest = KDNearestNeighbor(root->right,nearest,c,d+1);
  }

  return nearest;

}

void readFile(char* fileName)
{
  FILE* stream;
  char code[4], name[40], coord1[6], coord2[9], line[255];
  float lat, lon;
  nodePtr temp;

  if((stream = fopen("airport-locations.txt", "r"))==NULL)
	printf("File could not be opened...");


  while (fgets(line, 255, stream) != NULL){
	if (strchr(line,',') != NULL){
	  strncpy(code,strdup(line + 1),3);
	  code[3] = '\0';

	  strncpy(coord1,strdup(line + 6),5);
	  coord1[5] = '\0';
	  lat = atof(coord1);

	  strncpy(coord2,strdup(line + 12),8);
	  coord2[8] = '\0';
	  lon = atof(coord2);

	  strncpy(name,strdup(strchr(line,'\t') + 1),39);
	  char *p = strchr(name,'\n');
	  if (p != NULL)
		*p = '\0';

	  //name[39] = '\0';
	}

	//creates node for the data
	temp = newNode(strdup(code),strdup(name),lat,lon);
	//inserts new node into the tree
	root = KDInsert(root, temp);
  }

  fclose(stream);

}

findair_ret *findairport_1_svc(coordinatesA *argp, struct svc_req *rqstp)
{
  static findair_ret  result;
  airportList a;
  airportList* ap = &result.findair_ret_u.list;
  nodePtr nearest = NULL;

  if (begin == 0){
	readFile("airport_locations.txt");
	begin = 1;
  }

  nearest = KDNearestNeighbor(root, nearest, *argp, 0);

  //xdr_free((xdrproc_t)xdr_findair_ret, (char *)&result);
  
  int count = 0;
  while (count < 5){
	a = (airportData *) malloc(sizeof(airportData));
	a->airportName = ptrArray[count]->airport.airportName; 
	a->airportCode = ptrArray[count]->airport.airportCode;
	a->lat = ptrArray[count]->airport.lat;
	a->lon = ptrArray[count]->airport.lon;
	a->distance = ptrArray[count]->airport.distance;
	a->next = NULL;
	*ap = a;
	ap = &a->next; 
	
	count++; 
  }

  counter = 0;
  maxDist = 0;
  maxInd = 0;  
  result.err = 0;

  return &result;
}
