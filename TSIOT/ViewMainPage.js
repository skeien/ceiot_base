class ViewMainPage {
    showDevices(list, element) {
        let e = document.getElementById("devicesList");
        e.innerHTML = "";
        let list1 = [];
        let id;
        for (let device of list) {
            id=device.device_id;
            list1.push(id);
        	let image ;
            if (id>30){
            	image = "hot.png"}
            else{
            	image = "temp.png";}
            e.innerHTML += `<li class="collection-item avatar">
            <img src="images/${image}" alt="" class="circle">
            <span class="title">${device.name}</span>
            <p>id: ${id}</p>
            <p>key: ${device.key}</p>
          </li>  
          `;
        }
        let Eq_id=[];

        for (let i = 0; i < list1.length; i++) {
             for (let j = i + 1; j < list1.length; j++) {
                  if (list1[i] == list1[j]) {
                        Eq_id.push(list1[i]);
                  }
             }
        }   
	if (Eq_id){
        	window.alert("Los valores iguales son: "+ Eq_id);
        	}
    }
}
