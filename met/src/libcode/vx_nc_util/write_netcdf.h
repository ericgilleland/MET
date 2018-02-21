// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2017
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

////////////////////////////////////////////////////////////////////////

#ifndef  __WRITE_NETCDF_H__
#define  __WRITE_NETCDF_H__

////////////////////////////////////////////////////////////////////////

#include <netcdf>
using namespace netCDF;

#include "vx_grid.h"
#include "vx_config.h"
#include "nc_utils.h"
#include "observation.h"

////////////////////////////////////////////////////////////////////////
#define HDR_ARRAY_LEN    3   // Observation header length
#define OBS_ARRAY_LEN    5   // Observation values length
#define HEADER_STR_LEN   16  // Maximum length for header string
#define HEADER_STR_LEN_L 40  // Maximum length for header string (for time summary)

#define OBS_BUFFER_SIZE  (128 * 1024)

static const float FILL_VALUE = -9999.f;

////////////////////////////////////////////////////////////////////////

extern void write_netcdf_global     (NcFile *, const char *, const char *,
                                     const char *model_name = (const char *) 0,
                                     const char *desc       = (const char *) 0,
                                     const char *obtype     = (const char *) 0);
extern void write_netcdf_proj       (NcFile *, const Grid &);
extern void write_netcdf_latlon     (NcFile *, NcDim *, NcDim *, const Grid &);
extern void write_netcdf_grid_weight(NcFile *, NcDim *, NcDim *, const GridWeightType, const DataPlane &); 
extern void write_netcdf_var_times  (NcVar *, const DataPlane &);
extern void write_netcdf_var_times  (NcVar *, const unixtime, const unixtime, const int);

// Observations to NetCDF
extern int get_nc_header_index      ();
extern int get_nc_hdr_buf_count     ();
extern int get_nc_obs_buf_count     ();

extern void nc_obs_initialize       ();

extern void add_nc_header
     (const char *hdr_typ, const char *hdr_sid, const char *hdr_vld,
      const float hdr_lat, const float hdr_lon, const float hdr_elv);
extern void add_and_write_nc_observation
     (const NetcdfObsVars &obsVars,
      const float obs_arr[OBS_ARRAY_LEN], const char *obs_qty);

extern long count_nc_headers   (vector< Observation > &observations);

extern void create_nc_hdr_vars (NetcdfObsVars &obsVars, NcFile *, const int hdr_count, const int deflate_level=0);
extern void create_nc_obs_vars (NetcdfObsVars &obsVars, NcFile *, const int deflate_level=0, const bool use_var_id=true);

extern void init_nc_dims_vars  (NetcdfObsVars &obsVars, bool use_var_id = true);
extern void read_nc_dims_vars  (NetcdfObsVars &obsVars, NcFile *);

extern void reset_header_buffer(int buf_size);

extern void write_nc_headers        (const NetcdfObsVars &obsVars);
extern void write_nc_header_buffer  (const NetcdfObsVars &obsVars, const int buf_size);
extern void write_nc_obs_buffer     (const NetcdfObsVars &obsVars, const int buf_size);
extern int  write_nc_observations   (const NetcdfObsVars &obsVars, const vector< Observation > observations);
      

#endif   //  __WRITE_NETCDF_H__

////////////////////////////////////////////////////////////////////////