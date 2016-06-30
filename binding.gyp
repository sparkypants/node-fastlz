{
  "targets": [
    {
      "target_name": "FastLZ",
      "sources": [ "src/fastlz.cpp", "src/bindings.cpp" ],
      "include_dirs" : [
 	 		  "<!(node -e \"require('nan')\")"
		  ]
    }
  ],
}
