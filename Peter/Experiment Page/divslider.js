var loaded = false;
var mousedOver = false;
var topdiv;
var bottomdiv;
var detector;	
var slideDist = 0;
var maxSlide = -800;
var slideSteps = 20;
var i;
window.onload = function ()
{
	loaded = true;
	
	topdiv = document.getElementsByClassName('infront')[0];
	bottomdiv = document.getElementsByClassName('behind')[0];
	detector = document.getElementsByClassName('detector')[0];


		
	detector.onmouseover = function()
	{		
		if(!mousedOver)
		{			
			mousedOver = true;
			i=0;
			slideAway();
		}
	}
	
	detector.onmouseout = function()
	{		
		if(mousedOver)
		{
			mousedOver = false;			
			slideBack();
		}
	}
}


function slideAway()
{		
	if(i >= slideSteps || !mousedOver) {return;}
	i++;
	var currentPos = parseInt(window.getComputedStyle( topdiv, null ).getPropertyValue('left'));
	topdiv.style.left = (currentPos - (800/slideSteps)) + 'px';	
	setTimeout(slideAway, 20);	
}
	
function slideBack()
{		
	if(i <= 0 || mousedOver) {return;}
	i--;
	var currentPos = parseInt(window.getComputedStyle( topdiv, null ).getPropertyValue('left'));
	topdiv.style.left = (currentPos + (800/slideSteps)) + 'px';	
	setTimeout(slideBack, 20);	
}




	
