


########################################################################


GRID_STAT_EXEC = ${CORE_DIR}/grid_stat/grid_stat


########################################################################


   ##
   ##  grid_stat
   ##
   ##     prerequisites:  pcp_combine and gen_vx_mask
   ##


grid_stat: ${GRID_STAT_EXEC} pcp_combine gen_vx_mask
	@ echo
	@ echo "*** Running Grid-Stat on APCP using netCDF input for both forecast and observation ***"
	${GRID_STAT_EXEC} \
   	${TEST_OUT_DIR}/pcp_combine/sample_fcst_12L_2005080712V_12A.nc \
   	${TEST_OUT_DIR}/pcp_combine/sample_obs_2005080712V_12A.nc \
   	config/GridStatConfig_APCP_12 \
   	-outdir ${TEST_OUT_DIR}/grid_stat -v 2
	@ 
	@ echo
	@ echo "*** Running Grid-Stat on POP using a GRIB forecast and netCDF observation ***"
	${GRID_STAT_EXEC} \
   	../data/sample_fcst/2005080312/pop5km_2005080312F096.grib_G212 \
   	${TEST_OUT_DIR}/pcp_combine/sample_obs_2005080800V_12A.nc \
   	config/GridStatConfig_POP_12 \
   	-outdir ${TEST_OUT_DIR}/grid_stat -v 2
	@ 
	@ echo
	@ echo "*** Running Grid-Stat on APCP using a GRIB forecast and netCDF observation ***"
	${GRID_STAT_EXEC} \
   	../data/sample_fcst/2005080700/wrfprs_ruc13_24.tm00_G212 \
   	${TEST_OUT_DIR}/pcp_combine/sample_obs_2005080800V_24A.nc \
   	config/GridStatConfig_APCP_24 \
   	-outdir ${TEST_OUT_DIR}/grid_stat -v 2
	@ 
	@ echo
	@ echo "*** Running Grid-Stat using GRIB input for both forecast and observation ***"
	${GRID_STAT_EXEC} \
   	../data/sample_fcst/2005080700/wrfprs_ruc13_12.tm00_G212 \
   	../data/sample_fcst/2005080712/wrfprs_ruc13_00.tm00_G212 \
   	config/GridStatConfig_all \
   	-outdir ${TEST_OUT_DIR}/grid_stat -v 2
	@ 
	@ touch grid_stat


########################################################################


