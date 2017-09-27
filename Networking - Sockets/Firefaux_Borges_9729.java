import java.net.*;
import java.io.*;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;


class Firefaux_Borges_9729{

  public static void main(String[]args) throws Exception {
    String website = args[0];
    //String website = "https://people.cs.umass.edu/~arun/590CC/PA1/sample.html";
    int idx_double_backslash = website.indexOf("://");
    String server_substr = website.substring(idx_double_backslash + 3,website.length());

    int idx_next_backslash = server_substr.indexOf("/");
    String server = server_substr.substring(0,idx_next_backslash);
    //System.out.println(server);
    String file_path = server_substr.substring(idx_next_backslash,server_substr.length());
    //System.out.println(file_path);
    String [] names = file_path.split("/");
    String html_file_name = names[names.length-1];

    String signature = "\r\n\r\n";
    String image_tag = "<img src=";
    String image_file_name="";

    Socket socket = new Socket(server, 80);
    DataOutputStream dataOut = new DataOutputStream(socket.getOutputStream());
    dataOut.writeBytes("GET "+ file_path +" HTTP/1.0" + signature);

    DataInputStream dataIn = new DataInputStream(socket.getInputStream());

    OutputStream file = new FileOutputStream(html_file_name);
    int bytes_count, offset;
    byte[] chunk = new byte[2048];
    boolean html_found = false;
    while ((bytes_count = dataIn.read(chunk)) != -1)
    {
        //System.out.println(bytes_count);
        offset = 0;
        if(!html_found){
            String str = new String(chunk);
            int indexOf_html_start = str.indexOf(signature);
            if(indexOf_html_start != -1) {
                bytes_count = bytes_count - indexOf_html_start - 4;
                offset = indexOf_html_start+4;

                int indexOf_image_tag_start = str.indexOf("<img");
                String new_str = str.substring(indexOf_image_tag_start,str.length()-indexOf_image_tag_start);
                int indexOf_image_src = new_str.indexOf("src=");
                String new_str_src = new_str.substring(indexOf_image_src+5,new_str.length()-indexOf_image_src);
                int indexOf_image_end =  new_str_src.indexOf("\" ");
                //int indexOf_image_end_final = new_str_src.indexOf(0, indexOf_image_end);
                //System.out.println(new_str);
                //System.out.println(indexOf_image_end);
                image_file_name = new_str_src.substring(0,indexOf_image_end);
                //System.out.println(image_file_name);

                html_found = true;
            } else
                bytes_count = 0;
        }
      file.write(chunk, offset, bytes_count);
      file.flush();
    }
    dataIn.close();
    file.close();
    socket.close();


    StringBuilder buffer = new StringBuilder();
    String [] parts = file_path.split("/");
    for(int i=0;i<parts.length-1;i++){
      buffer.append(parts[i]+"/");
    }
    buffer.append(image_file_name.replaceAll("\\s",""));

    Socket socket2 = new Socket(server, 80);
    DataOutputStream dataOut2 = new DataOutputStream(socket2.getOutputStream());
    dataOut2.writeBytes("GET "+ buffer.toString() +" HTTP/1.0" + signature);
    DataInputStream dataIn2 = new DataInputStream(socket2.getInputStream());
    OutputStream imageFile = new FileOutputStream(image_file_name);

    boolean image_found = false;
    while ((bytes_count = dataIn2.read(chunk)) != -1)
    {
        //System.out.println(bytes_count);
        offset = 0;
        if(!image_found){
            String str = new String(chunk);
            int indexOf_image_start = str.indexOf(signature);
            if(indexOf_image_start != -1) {
                bytes_count = bytes_count - indexOf_image_start - 4;
                offset = indexOf_image_start+4;

                image_found = true;
            } else
                bytes_count = 0;

        }
      imageFile.write(chunk, offset, bytes_count);
      imageFile.flush();
    }
    dataIn2.close();
    file.close();



  }
}
