#include <bits/stdc++.h>
#include<fstream>
using namespace std ;

//load function data

unsigned char img_in_color[SIZE][SIZE][3] ;
unsigned char img_out_color[SIZE][SIZE][3] ;

// those functions copy and save images to do the process more than one time

void cpy_cl(){
    for (int i = 0; i < SIZE ; ++i) {
        for(int j = 0 ; j <SIZE ; ++j) {
            for(int l = 0 ; l < 3 ; l++){
                img_in_color[i][j][l] = img_out_color[i][j][l];
            }
        }
    }
}

void save_clr(){
    cout<<"Please enter target file name:"<<endl;
    string text ; cin >> text ;
    text = "images/" + text + ".bmp" ;
    writeRGBBMP(text.c_str() , img_in_color );
}

//=======================================================================

// Filters

//This filter convert images to black and white images
void B_W_F_cl(){
    unsigned char tempo[SIZE][SIZE] ;
    unsigned int mn = 255 , mx = 0 , avg ;
    unsigned int x=0;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            x = 0 ;
            for (int k = 0; k < 3; ++k) {
                x += img_in_color[i][j][k];
            }
            tempo[i][j] = x / 3 ;
            mn = min ( mn , x / 3 ) ;
            mx = max ( mx , x / 3 ) ;
        }
    }

    avg = ( mn + mx ) / 2  ;
    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0; j < SIZE ; j++ ) {
            ( tempo[i][j] >= avg ) ? tempo[i][j] = 255 : tempo[i][j] = 0 ;
            for(int k = 0 ; k < 3 ; k++){
                img_out_color[i][j][k] = tempo[i][j] ;
            }
        }
    }
    cpy_cl();
}

//This filter invert Grayscale images

void invert_f_cl(){
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            for(int l = 0 ; l < 3 ; l++){
                img_out_color[i][j][l] = 255 - img_in_color[i][j][l] ;
            }
        }
    }
    cpy_cl();
}

//This filter merge two or more  images

void merge_cl(){
    unsigned char img_in_cl[SIZE][SIZE][3] ;
    cout<<"Please enter name of image file to merge with:"<<"\n";
    char text[1000] = "" ;
    cin >> text ;
    strcat( text , ".bmp") ;
    ifstream in_file( text , std::ifstream::ate | std::ifstream::binary ) ;
    readRGBBMP(text , img_in_cl);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < 3; ++k){
                int avg=(img_in_cl[i][j][k]+img_in_color[i][j][k])/2;
                img_out_color[i][j][k]=avg;
            }
        }
    }
    cpy_cl();
}

//This filter flip  images horizontally or vertically

void FLIP_F_cl(){
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    char c;cin>>c;
    switch (c) {
        case 'v' :
            for (int i = 0; i <SIZE ; ++i) {
                for (int j = 0; j <SIZE ; ++j) {
                    for(int k = 0 ; k < 3 ; ++k ){
                        img_out_color[i][j][k]=img_in_color[SIZE-i-1][j][k]; //
                    }
                }
            }
            break;
        case 'h' :
            for (int i = 0; i <SIZE ; ++i) {
                for (int j = 0; j <SIZE ; ++j) {
                    for(int k = 0 ; k < 3 ; ++k){
                        img_out_color[i][j][k]=img_in_color[i][SIZE-j-1][k];
                    }
                }
            }
            break;
        default :
            break;
    }
    cpy_cl();
}

//This filter rotate images 90 or 180 or 270 degrees

void Rot_R_cl(){
    cout << "Rotate (90), (180) or (270) degrees?\n" ; int chc ; cin >> chc ;
    switch ( chc ) {
        case 90 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    for (int k = 0; k < 3; ++k) {
                        img_out_color[j][SIZE-i-1][k] = img_in_color[i][j][k] ;
                    }
                }
            }
            break ;
        case 180 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    for (int k = 0; k < 3 ; ++k) {
                        img_out_color[SIZE - 1 - i ][SIZE - 1 - j ][k] = img_in_color[i][j][k] ;
                    }
                }
            }
            break ;
        case 270 :
            for ( int i = 0 ; i < SIZE ; i++ ){
                for ( int j = 0 ; j < SIZE ; j++ ){
                    for (int k = 0; k < 3 ; ++k) {
                        img_out_color[SIZE - j - 1 ][i][k] = img_in_color[i][j][k] ;
                    }
                }
            }
            break;
        default :
            break;
    }
    cpy_cl();
}

//This filter lower or higher the opacity of images

void dark_light_cl(){
    cout<<"Do you want to (d)darken or (l)lighten?"<<"\n";
    char c; cin >> c;
    switch (c) {
        case 'l' :
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < 3; ++k) {
                        img_out_color[i][j][k] = (img_in_color[i][j][k] + (255)) / 2;
                    }
                }
            }
            break ;
        case 'd' :
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for (int k = 0; k < 3; ++k) {
                        img_out_color[i][j][k] = img_in_color[i][j][k] / 2;
                    }
                }
            }
            break;
        default :
            break ;
    }
    cpy_cl();
}

//This filter is detecting the edges of objects in images

void detect_edges_cl( ){
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j][k] = img_in_color[i][j][k] ;
            }
        }
    }

    unsigned char tempo[SIZE][SIZE] ;
    unsigned int x=0;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            x = 0 ;
            for (int k = 0; k < 3; ++k) {
                x += img_in_color[i][j][k];
            }
            tempo[i][j] = x / 3 ;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (abs(tempo[i][j]-tempo[i][j+1])>20)
                tempo[i][j]=0;
            else
                tempo[i][j]=255;
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j][k]=tempo[i][j];
            }
        }
    }
    cpy_cl();
}

//This filter  enlarges images to (1 or 2 or 3 or 4) quarter

void enlarge_cl(){
    cout << "Which quarter to enlarge 1, 2, 3 or 4?\n" ;
    int chc ; cin >> chc ;
    int dx[] { 0 , 0 ,  SIZE/2  ,  SIZE / 2 };
    int dy[] { 0 , SIZE / 2 , 0 , SIZE / 2  };
    for ( int i = 0 ; i < SIZE / 2 ; i++ ){
        for ( int j = 0 ; j < SIZE / 2 ; j++ ){
            for (int k = 0; k < 3; ++k) {
                unsigned char c = img_in_color[i + dx[chc-1]][j+dy[chc-1]][k] ;
                img_out_color[i*2][j*2][k] = c ;
                img_out_color[i*2 + 1 ][j*2][k] = c ;
                img_out_color[i*2][j*2 + 1 ][k] = c ;
                img_out_color[i*2 + 1 ][j*2+ 1][k] = c ;
            }
        }
    }
    cpy_cl();
}

//This filter shrinks images to (1/2 or 1/3 or 1/4)

void shrink_cl(){
    cout<<"Shrink to (1/2), (1/3) or (1/4)?"<<"\n";
    string s;
    cin>>s;
    for (int i = 0; i < SIZE; i++ ) {
        for (int j = 0; j < SIZE; j++ ) {
            for (int k = 0; k < 3 ; ++k) {
                img_out_color[i][j][k] = 255 ;
            }
        }
    }
    int x = ( s.back() - '0' ) ;
    for (int i = 0; i < SIZE; i+=2) {
        for (int j = 0; j < SIZE; j+=2) {
            for (int k = 0; k < 3 ; ++k) {
                img_out_color[i/x][j/x][k]=(img_in_color[i][j][k]+img_in_color[i+1][j][k]+img_in_color[i][j+1][k]+img_in_color[i+1][j+1][k])/4;
            }
        }
    }
    cpy_cl();
}

//This filter make a mirror copy of images to (left or right or upper or down)

void mir_cl(){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    for ( int i = 0 ; i < SIZE ; i++ )
        for ( int j = 0 ; j < SIZE ; j++ )
            for (int k = 0; k < 3 ; k++ )
                img_out_color[i][j][k] = img_in_color[i][j][k] ;
    char p ; cin >> p;
    switch ( p ) {
        case 'r' :
            for ( int i = 0; i < SIZE; i++ )
                for ( int j = 0 ; j < SIZE/2 ; j++ )
                    for ( int k = 0 ; k < 3 ; k++ )
                        img_out_color[i][j][k]=img_out_color[i][SIZE-j-1][k];
            break;
        case 'l' :
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE/2; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        img_out_color[i][SIZE-j-1][k]=img_out_color[i][j][k];
                    }
                }
            }
            break;
        case 'd' :
            for (int i = 0; i < SIZE/2; ++i)
                for (int j = 0; j < SIZE; ++j)
                    for(int k = 0; k < 3; ++k)
                        img_out_color[i][j][k]=img_out_color[SIZE-i-1][j][k];
            break;
        case 'u' :
            for (int i = 0; i < SIZE/2; ++i)
                for (int j = 0; j < SIZE; ++j)
                    for (int k = 0; k < 3; ++k)
                        img_out_color[SIZE-i-1][j][k]=img_out_color[i][j][k];
            break;
        default :
            break;
    }
    cpy_cl();
}

//This filter shuffle images by a specific order

void shuffle_img_cl( ){
    int dx[] { 0 , 0 , SIZE / 2 , SIZE / 2 } ;
    int dy[] { 0 , SIZE / 2 , 0 , SIZE / 2 } ;
    cout << "New order of quarters ? \n" ;
    vector<int> vv(4) ; for ( int i = 0 ; i < 4 ; i++ ) cin >> vv[i] ;

    for ( int i = 0 ; i < SIZE / 2 ; i++ ) {
        for ( int j = 0 ; j < SIZE / 2 ; j++ ) {
            for (int k = 0; k < 3; ++k) {
                img_out_color[i+dx[0]][j+dy[0]][k] = img_in_color[i+dx[vv[0]-1]][j+dy[vv[0]-1]][k] ; // 1st quad
                img_out_color[i+dx[1]][j+dy[1]][k] = img_in_color[i+dx[vv[1]-1]][j+dy[vv[1]-1]][k] ; // 2nd quad
                img_out_color[i+dx[2]][j+dy[2]][k] = img_in_color[i+dx[vv[2]-1]][j+dy[vv[2]-1]][k] ; // 3rd quad
                img_out_color[i+dx[3]][j+dy[3]][k] = img_in_color[i+dx[vv[3]-1]][j+dy[vv[3]-1]][k] ; // 4th quad
            }
        }
    }
    cpy_cl();
}

//This filter make a blur copy of images

void blur_cl(){
    int dx[] = { 1,0,0,-1,-1,1,-1,1};
    int dy[] = { 0,1,-1,0,1,1,-1,-1};
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k) {
                int avg = 1 , rot = img_in_color[i][j][k] ;
                for ( int m = 1 ; m <= 3 ; m++ ) {
                    for (int l = 0; l < 8; l++) {
                        int ni = i + dx[l] * m , nj = j + dy[l] * m ;
                        if ((ni >= 0 and nj >= 0 and ni < SIZE and nj < SIZE)) {
                            avg++;
                            rot += img_in_color[ni][nj][k];
                        }
                    }
                }
                img_out_color[i][j][k] = ( rot / avg ) ;
            }
        }
    }
    cpy_cl();
}

//This filter crops images

void crop_cl(){
    cout<<"Please enter x y l w \n";
    int x , y , l , w ; cin >> x >> y >> l >> w ;
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j][k] = 255 ;
            }
        }
    }
    for (int i = x ; i <= l ; i++ ) {
        for (int j = y; j <= w && j ; j++ ) {
            for (int k = 0; k < 3; ++k) {
                img_out_color[ (i - x) + ( ( SIZE - l ) / 2 ) ][ (j - y) + ( ( SIZE - w ) / 2 ) ][k] = img_in_color[i][j][k] ;
            }
        }
    }
    cpy_cl();
}

//This filter skew (stretch) images horizontally with a given degree

void skew_r_cl(){
    cout<<"Please enter degree to skew right :\n";
    unsigned char temp_img[SIZE][SIZE][3] ;
    double rad ;  cin >> rad ;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    int s = (int)(( 256 * 256 )/(( 256 / tan(rad) ) + 256 )) ;
    double mov = SIZE - s ; double step = ( 256.0 - s ) / 256.0  ;

    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j][k] = 255 ;
                temp_img[i][j][k] = 255 ;
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            for (int k = 0; k < 3; ++k) {
                temp_img[i][j][k] = img_in_color[i][(j*255)/s][k] ;
            }
        }
    }

    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j+(int)mov][k] = temp_img[i][j][k] ;
            }
        }
        mov -= step ;
    }
    cpy_cl();
}

//This filter skew (stretch) images vertically with a given degree

void skew_u_cl(){
    cout<<"Please enter degree to skew right :\n";
    unsigned char temp_img[SIZE][SIZE][3] ;
    double rad ;  cin >> rad ;
    rad = ( rad * 22 ) / ( 180 * 7 ) ;
    int s = (int)(( 256 * 256 )/(( 256 / tan(rad) ) + 256 )) ;
    double mov = SIZE - s ; double step = ( 256.0 - s ) / 256.0  ;

    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[i][j][k] = 255 ;
                temp_img[i][j][k] = 255 ;
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            for (int k = 0; k < 3; ++k) {
                temp_img[i][j][k] = img_in_color[(j*255)/s][i][k] ;
            }
        }
    }

    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < s ; j++ ){
            for (int k = 0; k < 3; ++k) {
                img_out_color[j+(int)mov][i][k] = temp_img[i][j][k] ;
            }
        }
        mov -= step ;
    }
    cpy_cl();
}

// ======================================================================
