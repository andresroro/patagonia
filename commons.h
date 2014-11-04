#define GRIDSIZE 15
#define HMRWS 0.001
#define HMRDS 0.002
#define LMRWS 0.007
#define LMRDS 0.005
#define CRWS 0.02
#define CRDS 0.01
#define DPRWS 0.01
#define DPRDS 0.005
#define WPRWS 0.02
#define WPRDS 0.01

enum PatchType { HM, LM, C, DP, WP };
enum Season { WET, DRY };

struct CInfo{
	int cID;
	int wf;
	int maxcc;
};

struct CInfo clans_in_patch[50];

