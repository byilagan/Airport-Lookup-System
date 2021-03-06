# This is a template Makefile generated by rpcgen

# Parameters

CLIENT = places_client
SERVER = places_server

ACLIENT = airports_client
ASERVER = airports_server

SOURCES_CLNT.c = 
SOURCES_CLNT.h = 
SOURCES_SVC.c = 
SOURCES_SVC.h = 
SOURCES.x = places.x

ASOURCES_CLNT.c =
ASOURCES_CLNT.h =
ASOURCES_SVC.c =
ASOURCES_SVC.h =
ASOURCES.x = airports.x

TARGETS_SVC.c = places_svc.c places_server.c places_xdr.c airports_xdr.c airports_clnt.c
TARGETS_CLNT.c = places_clnt.c places_client.c places_xdr.c 
TARGETS = places.h airports.h places_xdr.c places_clnt.c places_svc.c places_client.c places_server.c

ATARGETS_SVC.c = airports_svc.c airports_server.c airports_xdr.c 
ATARGETS_CLNT.c = airports_clnt.c airports_client.c airports_xdr.c
ATARGETS = airports.h airports_xdr.c airports_svc.c airports_client.c airports_server.c

OBJECTS_CLNT = $(SOURCES_CLNT.c:%.c=%.o) $(TARGETS_CLNT.c:%.c=%.o)
OBJECTS_SVC = $(SOURCES_SVC.c:%.c=%.o) $(TARGETS_SVC.c:%.c=%.o)

AOBJECTS_CLNT = $(ASOURCES_CLNT.c:%.c=%.o) $(ATARGETS_CLNT.c:%.c=%.o)
AOBJECTS_SVC = $(ASOURCES_SVC.c:%.c=%.o) -lm $(ATARGETS_SVC.c:%.c=%.o)

# Compiler flags 

CFLAGS += -g 
LDLIBS += -lnsl
RPCGENFLAGS = 

# Targets 

all : $(CLIENT) $(SERVER) $(ASERVER)

#$(TARGETS) : $(SOURCES.x)
#	rpcgen $(RPCGENFLAGS) $(SOURCES.x)

$(OBJECTS_CLNT) : $(SOURCES_CLNT.c) $(SOURCES_CLNT.h) $(TARGETS_CLNT.c) 

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c)

$(AOBJECTS_CLNT) : $(ASOURCES_CLNT.c) $(ASOURCES_CLNT.h) $(ATARGETS_CLNT.c)

$(AOBJECTS_SVC) : $(ASOURCES_SVC.c) $(ASOURCES_SVC.h) $(ATARGETS_SVC.c)

$(CLIENT) : $(OBJECTS_CLNT) 
	$(LINK.c) -o $(CLIENT) $(OBJECTS_CLNT) $(LDLIBS)

$(ACLIENT) : $(AOBJECTS_CLNT)
	$(LINK.c) -o $(ACLIENT) $(AOBJECTS_CLNT) $(LDLIBS)

$(SERVER) : $(OBJECTS_SVC) 
	$(LINK.c) -o $(SERVER) $(OBJECTS_SVC) $(LDLIBS)


#$(TARGETS) : $(SOURCES.x)
#	rpcgen $(RPCGENFLAGS) $(SOURCES.x)

$(ASERVER) : $(AOBJECTS_SVC)
	$(LINK.c) -o $(ASERVER) $(AOBJECTS_SVC) $(LDLIBS)


clean:
	$(RM) core $(TARGETS) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(CLIENT) $(SERVER)
