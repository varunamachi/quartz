
var apiKey = "";
var serverAddress = "";

function request(verb, endpoint, obj, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        print('xhr: on ready state change: ' + xhr.readyState)
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(http.status === 200) {
                var res = JSON.parse(xhr.responseText.toString())
                if(callback) cb(res);
            } else {
                //callback error
                //if(callback) cb(res);
            }
        }
    }
    var url = verb + ' ' + serverAddress + (endpoint ? ('/' + endpoint) :'' )
    print("Request: " + url)
    xhr.open(verb, url);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader('Accept', 'application/json');
    var data = obj ? JSON.stringify(obj) : ''
    xhr.send(data)
}

function login(userName, password, callback) {
    var http = new XMLHttpRequest()
    var url = serverAddress + "/login";
    var params = "username=" + userName + "&password=" +password;
    http.open("POST", url);

    //Send the proper header information along with the request
    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    http.setRequestHeader("Content-length", params.length);
    http.setRequestHeader("Connection", "close");
    http.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE && http.status === 200) {
            //logged in - success to callback
        } else {
            //error to callback
        }
    }
    http.send(params);
}


function getAllUsers(callback) {
    request("GET", "users", null, callback);
}

function getUser(userName, callback) {
    request("GET", "users/" + userName, callback );
}

function createUser(obj, callback) {
    request("POST", "users", obj, callback);
}

function updateUser(obj, callback) {
    request("PUT", "users", obj, callback);
}


