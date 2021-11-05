{
	"targets": [
		{
			"target_name": "emory",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"sources": [
				"./src/emory.cpp",
				"./src/index.cpp"
			],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
		}
	]
}