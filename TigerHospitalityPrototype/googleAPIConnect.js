function googleAPICall()
{
	var key = "003030";
	var url = "http://maps.googleapis.com/maps/api/js?key=";
	url += key;
	
	var script = document.createElement('script')
	script.src = url;
	script.onload = function()
	{
		alert("loaded, url = " + url);
	}
}