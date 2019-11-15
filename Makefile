TARGET=main
CGIPATH=/var/www/cgi-bin
cc=/usr/bin/gcc

BASE=-lgd -lpng -lz -ljpeg -lfreetype -lm
PNG_INCLUDE=-I/opt/libpng-1.6.37/include
PNG_LIB=-L/opt/libpng-1.6.37/lib
GD_INCLUDE=-I/opt/libgd-2.2.4/include
GD_LIB=-L/opt/libgd-2.2.4/lib
INC=-Iinclude $(PNG_INCLUDE) $(GD_INCLUDE) $(OPTIONS)
LIB=$(PNG_LIB) $(GD_LIB) $(BASE)

RM = rm -f

all: $(clean) libs.a get_data $(TARGET)

libs.a:
	@(cd ${MY_LIB_PATH};$(MAKE) cc=gcc)

$(TARGET): $(TARGET).c
	$(cc) $(INC) -o $@ $^ $(LIB) libs.a
	@ strip $@;chmod a+rx $@
	./$@&

get_data:get_data.c
	$(cc) $(INC) -o $@ $^ $(LIB) libs.a
	@ strip $@;chmod a+rx $@

%.o:%.c
	$(cc) $(INC) -c $<

%.o:%.cpp
	$(cc) $(INC) -Wno-deprecated -c $<

clean:
	-$(RM) *.[oa]
	-$(RM) $(TARGET)
