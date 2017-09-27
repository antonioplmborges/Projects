#include "fs.h"

using namespace std;


myFileSystem::myFileSystem(char diskName[16]) {
  // open the file with the above name
  // this file will act as the "disk" for your file system
  disk.open(diskName);

}

int myFileSystem::create_file(char name[8], int size) {
  //file name can be no longer than 8 characters
       if(strlen(name) > 8){
       return -1;
       }
        //max size of a file is 8 blocks
      if(size > 8 || size<0){
          return -1;
      }

    //create a file with this name and this size

    // high level pseudo code for creating a new file

    // Step 1: check to see if we have sufficient free space on disk by
    // reading in the free block list. To do this:
    // move the file pointer to the start of the disk file.
    char *buff = new char[128];
    disk.seekg(0);
    // Read the first 128 bytes (the free/in-use block information)
    disk.read(buff,128);
    // Scan the list to make sure you have sufficient free blocks to
    int free_block_count = 0; //for freeblocks index
    // allocate a new file of this size
    //char freeblocks[size];
    for(int i = 1; i < 128; i++) {
          if(free_block_count==size)
            break;
          if(buff[i]==0)
            free_block_count++;
    }

        //space requirements unmet
    if(free_block_count < size){
      return -1;
    }
        // Step 2: we look  for a free inode om disk
        //bollean capacityReached = false;
        int finode = 0;
        idxNode *node = new idxNode;
        for(int i = 128; i < 896; i += 48){
            disk.seekg(i);
            disk.read((char*)node, 48);
            if(node->used != 1){
              finode = i;
              node->size = size;
              node->used = 1;
              strcpy(node->name, name);
              break;
            }
            else
              continue;

          }
          if(finode == 0)
            return -1;

        node->used=1;
        strcpy(node->name, name);
        node->size = size;
        //can't allocate data blocks since all inodes are used
        //if(capacityReached ==true){
        //  return -1;
        //}
        // Step 3: Allocate data blocks to the file
        // for(i=0;i<size;i++)
        // Scan the block list that you read in Step 1 for a free block
        int blockNum = 0;
        for(int i = 0; i < size; i++){
          for(int j = 0; j < 128; j++){
            if(buff[j] == 0){
                blockNum = j;
                buff[j] = 1;
                break;
              }
            }
    node->blockPointers[i] = blockNum;
  }


      // Step 4: Write out the inode and free block list to disk
      //  Move the file pointer to the start of the file
      disk.seekp(0);
      disk.write(buff, 128);
      disk.seekp(finode);
      disk.write((char*)node, 48);
      delete node;
      return 1;

} // End Create

int myFileSystem::delete_file(char name[8]){
  // Delete the file with this name

  // Step 1: Locate the inode for this file
  // Move the file pointer to the 1st inode (129th byte)
  idxNode inode;
  int i;
  for(i = 0; i < 16; ++i) {
    char* inode_buf = new char[sizeof(idxNode)];
    disk.seekg(128 + 48 * i, disk.beg);
  // Read in an inode
  disk.read(inode_buf, sizeof(idxNode));
  memcpy(&inode, inode_buf, sizeof(idxNode));
  // If the inode is free, repeat above step.
  // If the inode is in use, check if the "name" field in the
  //   inode matches the file we want to delete. If not, read the next
  //   inode and repeat
    if(inode.used == 1 && strcmp(inode.name, name) == 0) { //if we find an inode with matching name

  // Step 2: free blocks of the file being deleted
  // Read in the 128 byte free block list (move file pointer to start
  //   of the disk and read in 128 bytes)
    char freeblockList[128];
    disk.seekg(0, disk.beg);
    disk.read(freeblockList, 128);
  // Free each block listed in the blockPointer fields as follows:
  // for(i=0;i< inode.size; i++)
    // freeblockList[ inode.blockPointer[i] ] = 0;
    int k;
    for(k = 0; k < inode.size; ++k) { //free the block
      freeblockList[inode.blockPointers[k]] = 0;
    }
  // Step 3: mark inode as free
  // Set the "used" field to 0.
    inode.used = 0; //free the index node
  // Step 4: Write out the inode and free block list to disk
  // Move the file pointer to the start of the file
    disk.seekg(0, disk.beg);

  disk.write(freeblockList,sizeof(freeblockList));  //write updated super block to disk
  // Move the file pointer to the position on disk where this inode was stored
  disk.seekg(128 + 48 * i, disk.beg);
  // Write out the inode
  memcpy(inode_buf, &inode,48);
  disk.write(inode_buf, sizeof(idxNode));
  return 1;
  }
}
return -1;
} // End Delete


int myFileSystem::ls(){

    idxNode *node = new idxNode;
    // for(i=0;i<16;i++)
    for(int i =0; i < 16; i++){
      // Move file pointer to the position of the 1st inode (129th byte)
      disk.seekg(128 + 48 *i, disk.beg);
      // REad in a inode
      disk.read((char*)node,sizeof(idxNode));

      if(node->used == 1){
        // print to the "name" and "size" fields from the inode
        //cout << node->name << " " << node->size << endl;
        }
      }// end for

    delete node;

    return -1;
}; // End ls

int myFileSystem::read(char name[8], int blockNum, char buf[1024]){
  // read this block from this file

    // Step 1: locate the inode for this file
    idxNode inode;
    char inode_buf[sizeof(idxNode)];
    for(int i = 0; i < 16; ++i) { //parse through inodes
        // Move file pointer to the position of the 1st inode (129th byte)
        disk.seekg(128 + 48 * i, disk.beg);
        // Read in an inode
        disk.read(inode_buf, sizeof(idxNode));
        memcpy(&inode, inode_buf,sizeof(inode));
        // If the inode is in use, compare the "name" field with the above file
        if(inode.used == 1 && strcmp(inode.name, name) == 0) { //if we find the node with matching name
            // Step 2: Read in the specified block
              // Check that blockNum < inode.size, else flag an error
              if(blockNum <= inode.size) { //make sure we have enough space

              // Get the disk address of the specified block
                // That is, addr = inode.blockPointer[blockNum]
                int addr = inode.blockPointers[blockNum];
                // Move the file pointer to the block location (i.e., to byte #
                //   addr*1024 in the file)
                disk.seekg(1024 * addr, disk.beg);
                // Read in the block => Read in 1024 bytes from this location
                //   into the buffer "buf"
                  disk.read(buf, 1024);
                  return 1;
                  }
            else {
                  return -1;
                  }
                }  // If the file names don't match, repeat
              }
              return -1;
  return -1;
} // End read


int myFileSystem::write(char name[8], int blockNum, char buf[1024]){
  // write this block to this file
    // Step 1: locate the inode for this file
    char inode_buf[sizeof(idxNode)];
    idxNode inode;
    for(int i = 0; i < 16; ++i) { //parse through inodes
      // Move file pointer to the position of the 1st inode (129th byte)
      disk.seekg(128 + 48 * i, disk.beg);
      // Read in a inode
      disk.read(inode_buf, sizeof(idxNode));
      memcpy(&inode, inode_buf, sizeof(inode));
      // If the inode is in use, compare the "name" field with the above file
      if(inode.used == 1 && strcmp(inode.name, name) == 0) { //if we find the node with matching name
        // Step 2: Write to the specified block
          // Check that blockNum < inode.size
        if(blockNum <= inode.size) { //make sure we have enough space
          // Get the disk address of the specified block
          // That is, addr = inode.blockPointer[blockNum]
          int addr = inode.blockPointers[blockNum];
          // Move the file pointer to the block location (i.e., byte # addr*1024)
          disk.seekg(1024 * addr, disk.beg);
          // Write the block! => Write 1024 bytes from the buffer "buff" to
          //   this location
          disk.write(buf, 1024);
          return 1;
        }
        else { //else flag an error
          return -1;
        }
      }   // If the file names don't match, repeat
    }
    return -1;
} // end write

int myFileSystem::close_disk(){

  disk.close();
// close the file(disk) opened in the constructor
// this is to check the persistency of file system
return -1;

    return 0;
}
