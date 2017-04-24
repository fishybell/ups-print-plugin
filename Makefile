REMOTESDKDIR=http://ftp.mozilla.org/pub/mozilla.org/mozilla/nightly/latest-1.7/
SDKFILE=gecko-sdk-i686-pc-linux-gnu.tar.gz

all: libupsprintplugin.so upsprint.xpi

libupsprintplugin.so: npshell.c npunix.c plugin.h gecko-sdk/unpacked
	gcc -shared -o libupsprintplugin.so -I ./gecko-sdk/include -O2 *.c
	cp libupsprintplugin.so xpi/plugins

upsprint.xpi: libupsprintplugin.so
	sh -c "cd xpi; zip -r upsprint.xpi install.js plugins/; mv upsprint.xpi .."

#Fetch the development kit from mozilla site
${SDKFILE}:
	wget -O ${SDKFILE} "${REMOTESDKDIR}${SDKFILE}"

#Unpack it
gecko-sdk/unpacked: ${SDKFILE}
	tar -xzf ${SDKFILE}
	touch gecko-sdk/unpacked

install:
	# "You should install this manually by copying the .so file"
	# "to the plugin directory of your mozilla browser installation."

clean:
	rm -f *.so
	rm -f *.xpi
	rm -f xpi/plugins/*.so

distclean: clean
	rm -r -f gecko-sdk gecko-sdk-i686-*.tar.gz
