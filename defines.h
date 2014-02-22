// Helper macros
#define SAFE_RELEASE(x) {if(x){(x)->Release();(x)=NULL;}}
#define SAFE_FREE_STRING(x) {if(x){SysFreeString(x);(x)=NULL;}}

// User Define RTC Event
#define WM_RTC_EVENT      WM_USER+100

#define QCIF_CX_SIZE  176
#define QCIF_CY_SIZE  144
#define QQCIF_CX_SIZE (QCIF_CX_SIZE/2)
#define QQCIF_CY_SIZE (QCIF_CY_SIZE/2)

struct SESSION_DATA {
	BSTR	bstrName;
	BSTR	bstrURI;
};
