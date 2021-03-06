#  ========================================================================
#  DEVise Data Visualization Software
#  (c) Copyright 2001-2016
#  By the DEVise Development Group
#  Madison, Wisconsin
#  All Rights Reserved.
#  ========================================================================
#
#  Under no circumstances is this software to be copied, distributed,
#  or altered in any way without prior permission from the DEVise
#  Development Group.

#  Makefile to set up peptide-cgi.

############################################################

#  $Id$

############################################################

# Defaults -- can be overridden in Makefile.config.
STAR_NAME_TEMPLATE = "bmr*.str"
ERROR_EMAIL = devise-sup@cs.wisc.edu
COMMENT_EMAIL = bmrbhelp@bmrb.wisc.edu
JAR_HOME = null
DO_CSR_DEFAULT = 0
LACS_LEVEL_DEFAULT = 0
LACS_NAME_TEMPLATE = bmr*_LACS.str
LACS_URL = null
UVD_CGI_URL = undefined
EXTRA_GC = 0
SPARTA_NAME_TEMPLATE = bmr*_SPARTA.str
SPARTA_URL = null
TORSION_ANGLE_SEARCH_TEMPLATE = "MRGridServlet\?pdb_id=*\&bmrb_id=\&block_text_type=4-filtered-FRED\&min_items=100\&db_username=wattos1"
DO_TAR_DEFAULT = 1
DO_RRTAR_DEFAULT = 1
DO_DIST_DEFAULT = 1
DO_RRDIST_DEFAULT = 1
DO_S2PRED_DEFAULT = 0
S2PRED_URL_DEFAULT = 
JS_CMD_PORT = 6666
DO_DYN_MOVIE_DEFAULT = 0
# <pdb> will get replaced with PDB ID
DYNAMICS_MOVIE_URL = "http://144.92.217.22/serve_video.php?key=\<pdb\>"
# <res> will get replaced with residue number
DYNAMICS_MOVIE_GEN_URL = "http://144.92.217.22/serve_video.php?key=\<pdb\>_devise_\<res\>"
DSSP_FILE_URL = http://www.bmrb.wisc.edu/ftp/pub/bmrb/derived_data/dssp/all

include Makefile.config

# The "real" directory (not symlink) for UVD sessions (must be
# a subdirectory of $(PEP_SESSION_HOME)).
UVD_SESSION_HOME = $(PEP_SESSION_HOME)/.uvd

# The "real" directory (not symlink) for UVD data (must be a
# subdirectory of $(PEP_DATA_HOME)).
UVD_DATA_HOME = $(PEP_DATA_HOME)/uvd

# The "real" directory (not symlink) for UVD html files (must be a
# subdirectory of $(PEP_HTML_HOME).
UVD_HTML_HOME = $(PEP_HTML_HOME)/uvd

S2D_PROPS_FILE = cgi-bin/s2d.props
ERROR_EMAIL_FILE = cgi-bin/error_email
VUR_CONFIG_FILE = cgi-bin/vur_config

#TEMP -- maybe add something to this target that removes obsolete directories (histograms/html, bmrb_home, vis_examples; other?)
setup: s2d_props bin error_email tmp vur_config
	cd html2; make setup

testsetup: do_testsetup
do_testsetup:
	mkdir test_html; cd test_html; ln -s ../html/* .
	mkdir test_data; cd test_data; ln -s ../data/* .
	mkdir test_session; cd test_session; ln -s ../dynamic_sessions/* .
	mkdir test_html_unreleased
	cd cgi-bin; ln -s ../test_html html_dir
	cd cgi-bin; ln -s ../test_data data_dir
	cd cgi-bin; ln -s ../test_session session_dir
	cd cgi-bin; ln -s ../test_html_unreleased html_unreleased
	cd cgi-bin; ln -s ../chem_info .
	cd cgi-bin; ln -s ../session_templates .
	cd cgi-bin; ln -s ../html_templates .
	cd cgi-bin; ln -s ../src/s2d.jar .
	# cd cgi-bin; ln -s ../html2/devise/peptide-cgi/figures .
	mkdir test_data/vis_server
	mkdir test_session/vis_server
	mkdir test_session/.unreleased
	mkdir test_data/uvd
	mkdir test_session/.uvd
	mkdir test_html/uvd
	cd test_html/uvd; ln -s ../../html/*.css .
	cd test_data; ln -s ../prototype/data/*.dat .

peaklist_setup:
	chmod g+rwx cgi-bin
	chmod g+rwx cgi-bin/tmp
	chmod g+rwx test_html test_data test_session

all:
	cd src; make all jar

test:
	cd cgi-bin; ./test_all

# Goofiness here is because we don't want to use Gnu make's .PHONY feature.
install: do_install histogram_install uvd_install example_install \
	movie_install
do_install: 
	./install $(DEV_DEMO_HOME) $(WWW_HOME) $(PEP_HOME) $(CGI_HOME) \
	  $(PEP_SESSION_HOME) $(PEP_DATA_HOME) $(PEP_HTML_HOME) \
	  $(JAR_HOME) $(INSTALL_MACHINE)

histogram_install:
	./install_histogram $(DEV_DEMO_HOME) $(WWW_HOME) \
	  $(HISTOGRAM_DATA_HOME) $(HISTOGRAM_HTML_HOME) $(PEP_HTML_HOME) \
          $(CODEBASE) $(OUTPUT_WEB_DOMAIN)

vur_install:
	./install -vur $(DEV_DEMO_HOME) /dev/null $(VUR_FRONTEND_DIR) \
	  $(VUR_CGI_HOME) $(VUR_SESSION_HOME) $(VUR_DATA_HOME) \
	  $(VUR_HTML_HOME) null $(VUR_INSTALL_MACHINE)

uvd_install: do_install
	./install_uvd $(UVD_SESSION_HOME) $(UVD_DATA_HOME) $(UVD_HTML_HOME) \
	  $(UVD_DATA_UPLOAD) $(CGI_HOME)

example_install:
	./install_examples $(CGI_HOME)

movie_install:
	cp -p html2/devise/vis_examples/dynamics_movie_demo.html \
		$(PEP_HOME)/../vis_examples
	cd $(CGI_HOME); ./generate_movies

proto_install:
	cp -p prototype/data/*.dat $(PEP_DATA_HOME)
	cp -p prototype/html2/*.html $(PEP_HTML_HOME)
	cp -p prototype/session/*.ds $(PEP_SESSION_HOME)
	mkdir -p $(PEP_HOME)/prototype/images
	cp -p prototype/html/*.html $(PEP_HOME)/prototype
	cp -p prototype/html/*.css $(PEP_HOME)/prototype
	cp -p prototype/html/images/*.* $(PEP_HOME)/prototype/images
	mkdir -p $(PEP_HOME)/prototype/bmrb_home_files
	cp -p prototype/html/bmrb_home_files/*.* $(PEP_HOME)/prototype/bmrb_home_files

# Note: this must *not* be done as part of the normal install; it's only
# for testing at CS, and doing the install at BMRB would goof things up.
home_install:
	cp -p html2/bmrb_home.html $(HTML_HOME)
	mkdir -p $(HTML_HOME)/bmrb_home_files
	cp -p html2/bmrb_home_files/*.* $(HTML_HOME)/bmrb_home_files
	mkdir -p $(HTML_HOME)/vis_serv
	cp -p html2/vis_serv/*.html $(HTML_HOME)/vis_serv

# Note: this must *not* be done as part of the normal install; it's only
# for testing at CS, and doing the install at BMRB would goof things up.
uvd_test_install:
	mkdir -p $(HTML_HOME)/uvd
	cp -p uvd*.html $(HTML_HOME)/uvd

clean:
	cd src; make clean
	-rm $(S2D_PROPS_FILE)
	-rm -rf cgi-bin/bin
	-rm -rf cgi-bin/tmp
	-rm $(ERROR_EMAIL_FILE)
	-rm $(VUR_CONFIG_FILE)
	-rm vur_config
	cd html2; make clean

testclean:
	-rm -rf test_data test_session test_html test_html_unreleased
	-rm cgi-bin/data_dir cgi-bin/session_dir cgi-bin/s2d.jar
	-rm cgi-bin/html_dir cgi-bin/html_unreleased
	-rm cgi-bin/session_templates cgi-bin/chem_info cgi-bin/html_templates
	# -rm cgi-bin/figures
	-rm -rf test_data/vis_server

dev_test:
	mkdir dev_test
	cd dev_test; ln -s ../scripts/*.pep .
	mkdir dev_test/dat
	mkdir dev_test/dat/bmrb
	cd dev_test/dat/bmrb; ln -s ../../../data/* .
	rm dev_test/dat/bmrb/CVS
	cd dev_test/dat/bmrb; ln -s ../../../histograms/dat/* .
	rm dev_test/dat/bmrb/CVS
	cd dev_test/dat/bmrb; ln -s ../../../test_data dynamic_data
	cd dev_test/dat/bmrb; ln -s $(HISTOGRAM_DATA_HOME) bmrb_histogram_data
	mkdir dev_test/schema
	touch dev_test/schema/catalog.dte
	cp /p/devise/demo/schema/schema/catalog.tcl dev_test/schema
	cp /p/devise/demo/schema/schema/Querycatalog.tcl dev_test/schema
	mkdir dev_test/schema/physical
	cd dev_test/schema/physical; ln -s ../../../schema/* .
	rm dev_test/schema/physical/CVS
	cd dev_test/schema/physical; ln -s ../../../histograms/schema/* .
	rm dev_test/schema/physical/CVS
	mkdir dev_test/session
	cd dev_test/session; ln -s ../../test_session bmrb
	cd dev_test/session; ln -s ../../session_templates .
	cd dev_test/session; ln -s ../../histograms/session histograms
	cd dev_test/session; ln -s ../../prototype/session prototype
	mkdir dev_test/cache

dev_testclean:
	-rm -rf dev_test

#  ========================================================================

s2d_props:
	-rm -f $(S2D_PROPS_FILE)
	echo "# Configuration-specific s2d properties" > $(S2D_PROPS_FILE)
	echo "bmrb_mirror.star_url=$(STAR_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.star_name_template=$(STAR_NAME_TEMPLATE)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.mmcif_template=$(MMCIF_TEMPLATE)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.3d_url=$(3D_EXAMPLE_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.summary_page_dir=$(SUMMARY_PAGE_DIR)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.cgi_url=$(CGI_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.uvd_cgi_url=$(UVD_CGI_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_csr_default=$(DO_CSR_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.comment_email=$(COMMENT_EMAIL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.lacs_level_default=$(LACS_LEVEL_DEFAULT)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.lacs_name_template=$(LACS_NAME_TEMPLATE)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.lacs_url=$(LACS_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.verbosity=0" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.debug_level=0" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.extra_gc=$(EXTRA_GC)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.sparta_name_template=$(SPARTA_NAME_TEMPLATE)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.sparta_url=$(SPARTA_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.restraint_grid_root=$(RESTRAINT_GRID_ROOT)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.torsion_angle_search_template=$(TORSION_ANGLE_SEARCH_TEMPLATE)" >> \
	  $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_tar_default=$(DO_TAR_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.remediated_restraints_template=$(REMEDIATED_RESTRAINTS_TEMPLATE)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_rrtar_default=$(DO_RRTAR_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_dist_default=$(DO_DIST_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_rrdist_default=$(DO_RRDIST_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_s2p_default=$(DO_S2PRED_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.s2p_url=$(S2PRED_URL_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.js_cmd_port=$(JS_CMD_PORT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.do_dyn_movie_default=$(DO_DYN_MOVIE_DEFAULT)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.dyn_movie_url=$(DYNAMICS_MOVIE_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.dyn_movie_gen_url=$(DYNAMICS_MOVIE_GEN_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.dssp_file_url=$(DSSP_FILE_URL)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.host=$(OUTPUT_WEB_DOMAIN)" >> $(S2D_PROPS_FILE)
	echo "bmrb_mirror.codebase=$(CODEBASE)" >> $(S2D_PROPS_FILE)

error_email:
	-rm -f $(ERROR_EMAIL_FILE)
	echo $(ERROR_EMAIL) > $(ERROR_EMAIL_FILE)

bin: cgi-bin/bin
cgi-bin/bin:
	mkdir cgi-bin/bin
	sed -e 's%java%$(JAVA_BIN)/java%' cgi-bin/java_tmpl > cgi-bin/bin/java
	chmod 755 cgi-bin/bin/java
	ln -s $(PERL_BIN)/perl cgi-bin/bin

tmp: cgi-bin/tmp
cgi-bin/tmp:
	mkdir cgi-bin/tmp
	chmod a+rwx cgi-bin/tmp

vur_config:
	-rm -f $(VUR_CONFIG_FILE)
	echo "# Configuration for viewing unreleased entries" > $(VUR_CONFIG_FILE)
	echo "set js_dir = $(VUR_JS_DIR)" >> $(VUR_CONFIG_FILE)
	echo "set input_dir = $(VUR_INPUT_DIR)" >> $(VUR_CONFIG_FILE)
	echo "set csr_lev = $(VUR_CSR_LEVEL)" >> $(VUR_CONFIG_FILE)
	echo "set vur_login = $(VUR_LOGIN)" >> $(VUR_CONFIG_FILE)
	echo "set vur_script = $(VUR_SCRIPT)" >> $(VUR_CONFIG_FILE)
	ln -s $(VUR_CONFIG_FILE) .
