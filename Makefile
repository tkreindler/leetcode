.PHONY: clean debug release

debug:
	@./build-debug.sh

release:
	@./build-release.sh

clean:
	rm -rf out build
